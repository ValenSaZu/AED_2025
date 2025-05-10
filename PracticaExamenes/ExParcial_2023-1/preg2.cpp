#include <iostream>
#include <vector>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CBinNode
{
    CBinNode(int _v)
    {
        value = _v; nodes[0] = nodes[1] = 0;
    }
    int value;
    CBinNode* nodes[2];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    CBinNode* Insert(int x);
    bool Remove(int x);
    void Print();
    CBinNode* getRoot() { return m_root; }
    void setRoot(CBinNode* node) { m_root = node; }
private:
    bool Find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void InOrder(CBinNode* n);
    CBinNode* m_root;
    bool m_b;
};

CBinTree::CBinTree()
{
    m_root = 0;
    m_b = 0;
}

CBinTree::~CBinTree()
{
    // ?
}

bool CBinTree::Find(int x, CBinNode**& p)
{
    for (p = &m_root;
        *p && (*p)->value != x;
        p = &((*p)->nodes[(*p)->value < x]));
    return *p && (*p)->value == x;
}

CBinNode* CBinTree::Insert(int x)
{
    CBinNode** p;
    if (Find(x, p)) return 0;
    *p = new CBinNode(x);
    return *p;
}
bool CBinTree::Remove(int x)
{
    CBinNode** p;
    if (!Find(x, p)) return 0;
    if ((*p)->nodes[0] && (*p)->nodes[1])
    {
        CBinNode** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    CBinNode* t = *p;
    *p = (*p)->nodes[(*p)->nodes[0] == 0];
    delete t;
    return 1;
}

CBinNode** CBinTree::Rep(CBinNode** q)
{
    m_b = !m_b;
    q = &((*q)->nodes[!m_b]);
    while ((*q)->nodes[m_b])
        q = &((*q)->nodes[m_b]);
    return q;
}

void CBinTree::InOrder(CBinNode* n)
{
    if (!n) return;
    InOrder(n->nodes[0]);
    cout << n->value << " ";
    InOrder(n->nodes[1]);
}

void CBinTree::Print()
{
    InOrder(m_root);
    cout << endl;
}

class CMaxHeap
{
public:
    CBinTree l;
    vector<CBinNode*> max;
    void recalculate(CBinNode* n);
    void push(int x);
    int pop();
    int top();
    void print();
};

void CMaxHeap::recalculate(CBinNode* n)
{
    while (n) {
        max.push_back(n);
        n = n->nodes[1];
    }
}

void CMaxHeap::push(int x)
{
    CBinNode* node = l.Insert(x);
    if (max.empty()) {
        max.push_back(node);
    }
    else {
        if (max.back()->value < x) {
            max.push_back(node);
        }
    }
}

int CMaxHeap::pop()
{
    if (!max.empty()) {
        CBinNode* exMax = max.back();
        int valExMax = exMax->value;
        if (exMax == l.getRoot() && exMax->nodes[0]) {
            l.setRoot(exMax->nodes[0]);
            recalculate(exMax->nodes[0]);
        }
        else if (exMax->nodes[0]) {
            CBinNode* minSon = exMax->nodes[0];
            max.pop_back();
            max.back()->nodes[1] = minSon;
            max.push_back(minSon);
        }
        else {
            max.pop_back();
            max.back()->nodes[1] = nullptr;
        }
        delete exMax;
        return valExMax;
    }
    else {
        return 0;
    }
}

int CMaxHeap::top()
{
    if (!max.empty()) {
        return max.back()->value;
    }
    else {
        return 0;
    }
}

void CMaxHeap::print() {
    l.Print();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    CBinTree t;

    t.Insert(50); t.Insert(30); t.Insert(60);
    t.Insert(80); t.Insert(55); t.Insert(11);
    t.Insert(33); t.Insert(5); t.Insert(14);
    t.Insert(31); t.Insert(48);
    t.Print();

    CMaxHeap mh;
    mh.push(50); mh.push(30); mh.push(60);
    mh.push(80); mh.push(55); mh.push(11);
    mh.push(33); mh.push(5); mh.push(14);
    mh.push(31); mh.push(48);

    mh.print();

    cout << mh.top() << endl; mh.pop();
    mh.print();
    cout << mh.top() << endl; mh.pop();
    mh.print();
    cout << mh.top() << endl; mh.pop();
    mh.print();
    cout << mh.top() << endl; mh.pop();
    mh.print();
}
