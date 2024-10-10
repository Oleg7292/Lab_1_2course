#include "Stack.h"
#include <iostream>
#include <stdexcept>

void Stack::initialize(size_t initialCapacity) {
    capacity = initialCapacity;
    top = 0;
    data = new int[capacity];
}

void Stack::resize() {
    capacity *= 2;
    int* newData = new int[capacity];
    for (size_t i = 0; i < top; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

void Stack::push(int value) {
    if (top >= capacity) {
        resize();
    }
    data[top++] = value;
}

int Stack::pop() {
    if (top == 0) {
        throw std::out_of_range("Stack underflow");
    }
    return data[--top];  // Уменьшаем top и возвращаем элемент
}


int Stack::top_elem() const {
    if (top == 0) {
        throw std::out_of_range("Stack is empty");
    }
    return data[top - 1];
}

void Stack::cleanup() {
    delete[] data;
}
