#include "DoublyLinkedList.h"
#include <iostream>

// Инициализация списка
void DoublyLinkedList::initialize() {
    head = nullptr;
    tail = nullptr;
}

// Добавление элемента в начало списка
void DoublyLinkedList::push_front(int value) {
    DoublyNode* newNode = new DoublyNode{value, nullptr, head};
    if (head) {
        head->prev = newNode;
    } else {
        tail = newNode;  // Если список был пуст, новый элемент — это и хвост
    }
    head = newNode;
}

// Добавление элемента в конец списка
void DoublyLinkedList::push_back(int value) {
    DoublyNode* newNode = new DoublyNode{value, tail, nullptr};
    if (tail) {
        tail->next = newNode;
    } else {
        head = newNode;  // Если список был пуст, новый элемент — это и голова
    }
    tail = newNode;
}

// Удаление элемента по значению
void DoublyLinkedList::remove(int value) {
    DoublyNode* temp = head;
    while (temp && temp->data != value) {
        temp = temp->next;
    }
    
    if (!temp) {
        std::cerr << "Value not found in list\n";
        return;
    }
    
    if (temp->prev) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next;  // Если удаляется голова
    }

    if (temp->next) {
        temp->next->prev = temp->prev;
    } else {
        tail = temp->prev;  // Если удаляется хвост
    }

    delete temp;
}

// Печать списка в прямом порядке
void DoublyLinkedList::print_forward() const {
    DoublyNode* temp = head;
    while (temp) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

// Печать списка в обратном порядке
void DoublyLinkedList::print_backward() const {
    DoublyNode* temp = tail;
    while (temp) {
        std::cout << temp->data << " ";
        temp = temp->prev;
    }
    std::cout << std::endl;
}

// Очистка памяти
void DoublyLinkedList::cleanup() {
    while (head) {
        DoublyNode* toDelete = head;
        head = head->next;
        delete toDelete;
    }
    tail = nullptr;
}
