#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>

using namespace std;

struct ListNode { 
    string data;
    ListNode* next;
};

struct LinkedList {
    ListNode* head;

    void initialize();
    void push_front(const string& value);
    void push_back(const string& value);
    void remove_front();
    void remove_back();
    void remove(const string& value);
    bool find(const string& value) const;
    void cleanup();
};

#endif
