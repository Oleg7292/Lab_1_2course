#ifndef COMPLETEBINARYTREE_H
#define COMPLETEBINARYTREE_H

struct CompleteBinaryTree {
    int* nodes;
    int capacity;
    int size;

    void initialize(int initialCapacity = 10);
    void resize();
    void insert(int value);
    bool isComplete() const;
    void print() const;
    void cleanup();
};

#endif
