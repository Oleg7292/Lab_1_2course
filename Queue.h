#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>

template <typename T>
struct QueueNode {
    T data;
    QueueNode* next;
    QueueNode* prev;
};

template <typename T>
struct Queue {
    QueueNode<T>* head;
    QueueNode<T>* tail;

    Queue() : head(nullptr), tail(nullptr) {}
    ~Queue() { cleanup(); }

    void initialize() {
        head = nullptr;
        tail = nullptr;
    }

    void push(const T& value) {
        QueueNode<T>* newQueueNode = new QueueNode<T>;
        newQueueNode->data = value;
        newQueueNode->next = nullptr;
        newQueueNode->prev = tail;

        if (tail) {
            tail->next = newQueueNode;
        } else {
            head = newQueueNode;
        }

        tail = newQueueNode;
    }

    void pop() {
        if (!head) {
            std::cerr << "Queue underflow\n";
            return;
        }

        QueueNode<T>* toDelete = head;
        head = head->next;

        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }

        delete toDelete;
    }

    T front_elem() const {
        if (!head) {
            throw std::out_of_range("Queue is empty");
        }
        return head->data;
    }

    bool is_empty() const {
        return head == nullptr;
    }

    void cleanup() {
        while (head) {
            QueueNode<T>* toDelete = head;
            head = head->next;
            delete toDelete;
        }
        tail = nullptr;
    }
};

#endif