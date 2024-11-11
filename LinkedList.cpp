#include "LinkedList.h"
#include <iostream>

using namespace std;

void LinkedList::initialize() {
    head = nullptr;
}

void LinkedList::push_front(const string& value) {
    ListNode* newListNode = new ListNode;
    newListNode->data = value;
    newListNode->next = head;
    head = newListNode;
}

void LinkedList::push_back(const string& value) {
    ListNode* newListNode = new ListNode;
    newListNode->data = value;
    newListNode->next = nullptr;
    if (!head) {
        head = newListNode;
    } else {
        ListNode* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newListNode;
    }
}

void LinkedList::remove(const string& value) {
    if (!head) return;

    if (head->data == value) {
        ListNode* toDelete = head;
        head = head->next;
        delete toDelete;
        return;
    }

    ListNode* temp = head;
    while (temp->next && temp->next->data != value) {
        temp = temp->next;
    }

    if (temp->next) {
        ListNode* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
    }
}

void LinkedList::remove_front() {
    if (!head) return;
    ListNode* toDelete = head;
    head = head->next;
    delete toDelete;
}

void LinkedList::remove_back() {
    if (!head) return;

    if (!head->next) {
        delete head;
        head = nullptr;
        return;
    }

    ListNode* temp = head;
    while (temp->next->next) {
        temp = temp->next;
    }

    delete temp->next;
    temp->next = nullptr;
}

bool LinkedList::find(const string& value) const {
    ListNode* temp = head;
    while (temp) {
        if (temp->data == value) return true;
        temp = temp->next;
    }
    return false;
}

void LinkedList::cleanup() {
    while (head) {
        ListNode* toDelete = head;
        head = head->next;
        delete toDelete;
    }
}