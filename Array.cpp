#include "Array.h"
#include <stdexcept>
#include <iostream>

void Array::initialize(size_t initialCapacity) {
    capacity = initialCapacity;
    length = 0;
    data = new int[capacity];
}

void Array::resize() {
    capacity *= 2;
    int* newData = new int[capacity];
    for (size_t i = 0; i < length; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

void Array::add(int value) {
    if (length >= capacity) {
        resize();
    }
    data[length++] = value;
}

int Array::get(size_t index) const {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

void Array::removeAt(size_t index) {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    for (size_t i = index; i < length - 1; ++i) {
        data[i] = data[i + 1];
    }
    length--;
}

void Array::cleanup() {
    delete[] data;
}
