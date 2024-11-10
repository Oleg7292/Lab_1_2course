#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <string>

using namespace std;

struct DoublyNode {
    string data;
    DoublyNode* prev;
    DoublyNode* next;
};

struct DoublyLinkedList {
    DoublyNode* head;
    DoublyNode* tail;

    void initialize();
    void push_front(const string& value);
    void push_back(const string& value);
    void remove(const string& value);
    void cleanup();
};

#endif
