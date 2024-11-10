#ifndef COMPLETEBINARYTREE_H
#define COMPLETEBINARYTREE_H

#include <iostream>
using namespace std;

struct CompleteBinaryTree {
    int value;
    CompleteBinaryTree* left;
    CompleteBinaryTree* right;

    CompleteBinaryTree(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Функции для работы с полным бинарным деревом
CompleteBinaryTree* initialize();
bool isComplete(CompleteBinaryTree* root);                        // Инициализация дерева
void insert(CompleteBinaryTree*& root, int value);       // Вставка элемента
bool find(CompleteBinaryTree* root, int value);          // Поиск элемента
void remove(CompleteBinaryTree*& root, int value);       // Удаление элемента

#endif
