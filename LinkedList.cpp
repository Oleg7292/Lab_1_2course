#include "LinkedList.h"
#include <iostream>

void LinkedList::initialize() {
    head = nullptr;
}

void LinkedList::push_front(int value) {
    Node* newNode = new Node{value, head};
    head = newNode;
}

void LinkedList::push_back(int value) {
    Node* newNode = new Node{value, nullptr};
    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void LinkedList::remove(int value) {
    if (!head) return;

    if (head->data == value) {
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
        return;
    }

    Node* temp = head;
    while (temp->next && temp->next->data != value) {
        temp = temp->next;
    }

    if (temp->next) {
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
    }
}

void LinkedList::cleanup() {
    while (head) {
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
    }
}
