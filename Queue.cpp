#include "Queue.h"
#include <iostream>
#include <stdexcept>

void Queue::initialize(size_t initialCapacity) {
    capacity = initialCapacity;
    data = new int[capacity];
    front = 0;
    back = 0;
    count = 0;
}

void Queue::resize() {
    capacity *= 2;
    int* newData = new int[capacity];
    for (size_t i = 0; i < count; ++i) {
        newData[i] = data[(front + i) % capacity];
    }
    delete[] data;
    data = newData;
    front = 0;
    back = count;
}

void Queue::push(int value) {
    if (count == capacity) {
        resize();
    }
    data[back] = value;
    back = (back + 1) % capacity;
    count++;
}

void Queue::pop() {
    if (count == 0) {
        std::cerr << "Queue underflow\n";
        return;
    }
    front = (front + 1) % capacity;
    count--;
}

int Queue::front_elem() const {
    if (count == 0) {
        throw std::out_of_range("Queue is empty");
    }
    return data[front];
}

void Queue::cleanup() {
    delete[] data;
}
