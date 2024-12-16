#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;

    DoublyLinkedList();
    void insertHead(int value);
    void insertTail(int value);
    void insertAt(int value, int position);
    void deleteHead();
    void deleteTail();
    void deleteAt(int position);
    Node* search(int value);
    void clear();
    ~DoublyLinkedList();
};

#endif // DOUBLYLINKEDLIST_H
