#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>

struct Queue {
    int* data;
    size_t capacity;
    size_t front;
    size_t back;
    size_t count;

    void initialize(size_t initialCapacity = 2);
    void resize();
    void push(int value);
    void pop();
    int front_elem() const;
    void cleanup();
};

#endif
