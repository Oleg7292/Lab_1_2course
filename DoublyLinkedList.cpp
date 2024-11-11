#include "DoublyLinkedList.h"
#include <iostream>

using namespace std;

void DoublyLinkedList::initialize() {
    head = nullptr;
    tail = nullptr;
}

void DoublyLinkedList::push_front(const string& value) {
    DoublyNode* newNode = new DoublyNode;
    newNode->data = value;
    newNode->next = head;
    newNode->prev = nullptr;
    
    if (head) {
        head->prev = newNode;
    } else {
        tail = newNode;
    }
    head = newNode;
}

void DoublyLinkedList::push_back(const string& value) {
    DoublyNode* newNode = new DoublyNode;
    newNode->data = value;
    newNode->prev = tail;
    newNode->next = nullptr;
    
    if (tail) {
        tail->next = newNode;
    } else {
        head = newNode;
    }
    tail = newNode;
}

void DoublyLinkedList::remove(const string& value) {
    DoublyNode* temp = head;
    
    while (temp && temp->data != value) {
        temp = temp->next;
    }
    
    if (!temp) return;

    if (temp->prev) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next;
    }

    if (temp->next) {
        temp->next->prev = temp->prev;
    } else {
        tail = temp->prev;
    }

    delete temp;
}

void DoublyLinkedList::remove_front() {
    if (!head) return;

    DoublyNode* toDelete = head;
    head = head->next;
    
    if (head) {
        head->prev = nullptr;
    } else {
        tail = nullptr;  // Если список стал пустым
    }
    
    delete toDelete;
}

void DoublyLinkedList::remove_back() {
    if (!tail) return;

    DoublyNode* toDelete = tail;
    tail = tail->prev;
    
    if (tail) {
        tail->next = nullptr;
    } else {
        head = nullptr;  // Если список стал пустым
    }
    
    delete toDelete;
}

bool DoublyLinkedList::find(const string& value) const {
    DoublyNode* temp = head;
    while (temp) {
        if (temp->data == value) return true;
        temp = temp->next;
    }
    return false;
}

void DoublyLinkedList::cleanup() {
    while (head) {
        DoublyNode* toDelete = head;
        head = head->next;
        delete toDelete;
    }
    tail = nullptr;
}