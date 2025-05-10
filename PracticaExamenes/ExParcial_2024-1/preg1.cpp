#include <iostream>

using namespace std;

class node
{
public:
    int data;
    node* next;
    node(int val) {
        data = val;
        next = 0;
    }
};

class CircularLinkedList
{
    node* head = NULL;
public:
    void add(int value)
    {
        //TO DO
        node* newNode = new node(value);
        node* recor = head;
        if (!head) {
            head = newNode;
        }
        else {
            for (; recor->next != head; recor = recor->next);
            recor->next = newNode;
        }
        newNode->next = head;
    }

    void del(int value)
    {
        // TO DO
        node* recor = head;
        for (; recor->next != head && recor->next->data != value; recor = recor->next);
        if (head->next == head) {
            head = nullptr;
            delete recor;
        }
        else {
            node* tmp = recor->next;
            recor->next = tmp->next;
            delete tmp;
        }
    }

    void print()
    {
        int cont = 0;
        node* ptr = head;
        cout << "head->";
        while (head && cont < 1)
        {
            cout << ptr->data << " -> ";
            ptr = ptr->next;
            if (ptr == head) cont++;
        }
        if (head) cout << ptr->data;
        cout << " <- head \n ";

    }
};

int main()
{
    int ADD[10] = { 2,4,6,8,10,1,3,5,7,9 };
    int DEL[10] = { 9,7,5,3,1,10,8,6,4,2 };
    CircularLinkedList CLL;
    for (int i = 0; i < 10; i++)
    {
        cout << "ADD " << ADD[i] << endl;
        CLL.add(ADD[i]);
        CLL.print();
    }

    for (int i = 0; i < 10; i++)
    {
        cout << "DEL " << DEL[i] << endl;
        CLL.del(DEL[i]);
        CLL.print();
    }
}