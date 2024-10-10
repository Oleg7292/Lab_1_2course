#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct Node {
    int data;
    Node* next;
};

struct LinkedList {
    Node* head;

    void initialize();
    void push_front(int value);
    void push_back(int value);
    void remove(int value);
    void cleanup();
};

#endif
