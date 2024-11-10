#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>

using namespace std;

struct ListNode {  // Переименовано
    string data;
    ListNode* next;
};

struct LinkedList {
    ListNode* head;

    void initialize();
    void push_front(const string& value);
    void push_back(const string& value);
    void remove(const string& value);
    void cleanup();
};

#endif
