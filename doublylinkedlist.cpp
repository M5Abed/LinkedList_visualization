#include "doublylinkedlist.h"

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

void DoublyLinkedList::insertHead(int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void DoublyLinkedList::insertTail(int value) {
    Node* newNode = new Node(value);
    if (!tail) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

void DoublyLinkedList::insertAt(int value, int position) {
    if (position <= 0) {
        insertHead(value);
        return;
    }

    Node* current = head;
    for (int i = 0; current && i < position - 1; ++i) {
        current = current->next;
    }

    if (!current) {
        insertTail(value);
        return;
    }

    Node* newNode = new Node(value);
    newNode->next = current->next;
    newNode->prev = current;

    if (current->next) {
        current->next->prev = newNode;
    }

    current->next = newNode;

    if (!newNode->next) {
        tail = newNode;
    }
}

void DoublyLinkedList::deleteHead() {
    if (!head) return;

    Node* temp = head;
    head = head->next;

    if (head) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }

    delete temp;
}

void DoublyLinkedList::deleteTail() {
    if (!tail) return;

    Node* temp = tail;
    tail = tail->prev;

    if (tail) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }

    delete temp;
}

void DoublyLinkedList::deleteAt(int position) {
    if (position < 0 || !head) return;

    if (position == 0) {
        deleteHead();
        return;
    }

    Node* current = head;
    for (int i = 0; current && i < position; ++i) {
        current = current->next;
    }

    if (!current) return;

    if (current->prev) {
        current->prev->next = current->next;
    }

    if (current->next) {
        current->next->prev = current->prev;
    }

    if (current == tail) {
        tail = current->prev;
    }

    delete current;
}

Node* DoublyLinkedList::search(int value) {
    Node* current = head;
    while (current) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void DoublyLinkedList::clear() {
    while (head) {
        deleteHead();
    }
}

DoublyLinkedList::~DoublyLinkedList() {
    clear();
}
