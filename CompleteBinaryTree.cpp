#include "CompleteBinaryTree.h"
#include <iostream>
#include <cmath>

void CompleteBinaryTree::initialize(int initialCapacity) {
    capacity = initialCapacity;
    nodes = new int[capacity];
    size = 0;
}

void CompleteBinaryTree::resize() {
    capacity *= 2;
    int* newNodes = new int[capacity];
    for (int i = 0; i < size; ++i) {
        newNodes[i] = nodes[i];
    }
    delete[] nodes;
    nodes = newNodes;
}

void CompleteBinaryTree::insert(int value) {
    if (size >= capacity) {
        resize();
    }
    nodes[size++] = value;
}

bool CompleteBinaryTree::isComplete() const {
    int height = std::floor(std::log2(size)) + 1;
    int maxNodes = std::pow(2, height) - 1;
    return size == maxNodes;
}

void CompleteBinaryTree::print() const {
    for (int i = 0; i < size; ++i) {
        std::cout << nodes[i] << " ";
    }
    std::cout << std::endl;
}

void CompleteBinaryTree::cleanup() {
    delete[] nodes;
}
