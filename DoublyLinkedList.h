#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

// Структура узла двусвязного списка
struct DoublyNode {
    int data;
    DoublyNode* prev;
    DoublyNode* next;
};

// Двусвязный список
struct DoublyLinkedList {
    DoublyNode* head;
    DoublyNode* tail;

    void initialize();
    void push_front(int value);
    void push_back(int value);
    void remove(int value);
    void cleanup();
    void print_forward() const;
    void print_backward() const;
};

#endif
