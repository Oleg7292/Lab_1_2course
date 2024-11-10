#include "Stack.h"
#include <iostream>
#include <stdexcept>

using namespace std;

void Stack::initialize() {
    top = nullptr;
}

void Stack::push(const string& value) {
    StackNode* newStackNode = new StackNode;
    newStackNode->data = value;
    newStackNode->next = top;
    top = newStackNode;  // Новый элемент становится вершиной стека
}

void Stack::pop() {
    if (!top) {
        cerr << "Stack underflow\n";
        return;
    }
    StackNode* toDelete = top;
    top = top->next;  // Сдвигаем вершину вниз
    delete toDelete;  // Удаляем старую вершину
}

string Stack::top_elem() const {
    if (!top) {
        throw out_of_range("Stack is empty");
    }
    return top->data;  // Возвращаем строку из вершины стека
}

void Stack::cleanup() {
    while (top) {
        StackNode* toDelete = top;
        top = top->next;
        delete toDelete;
    }
}
