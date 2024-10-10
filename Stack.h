#ifndef STACK_H
#define STACK_H

#include <cstddef>

struct Stack {
    int* data;
    size_t top;
    size_t capacity;

    void initialize(size_t initialCapacity = 2);
    void resize();
    void push(int value);
    int pop();
    int top_elem() const;
    void cleanup();
};

#endif
