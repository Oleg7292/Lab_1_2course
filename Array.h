#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>  // Для size_t

struct Array {
    int* data;
    size_t capacity;
    size_t length;

    void initialize(size_t initialCapacity = 2);
    void resize();
    void add(int value);
    int get(size_t index) const;
    void removeAt(size_t index);
    void cleanup();
};

#endif
