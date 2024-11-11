#include "CompleteBinaryTree.h"
#include "Queue.h" 
#include <iostream>

CompleteBinaryTree* initialize() {
    return nullptr;
}

bool isComplete(CompleteBinaryTree* root) {
    if (root == nullptr) return true;  // Пустое дерево считается полным

    Queue<CompleteBinaryTree*> q;
    q.initialize();
    q.push(root);

    bool foundNonFullNode = false;  // Флаг, который указывает, что мы нашли неполный узел

    while (!q.is_empty()) {
        CompleteBinaryTree* current = q.front_elem();
        q.pop();

        // Проверяем левый дочерний узел
        if (current->left) {
            if (foundNonFullNode) {
                q.cleanup();
                return false;  // Если уже был найден неполный узел, дерево не полное
            }
            q.push(current->left);
        } else {
            foundNonFullNode = true;  // Если нет левого узла, устанавливаем флаг
        }

        // Проверяем правый дочерний узел
        if (current->right) {
            if (foundNonFullNode) {
                q.cleanup();
                return false;  // Если уже был найден неполный узел, дерево не полное
            }
            q.push(current->right);
        } else {
            foundNonFullNode = true;  // Если нет правого узла, устанавливаем флаг
        }
    }

    q.cleanup();
    return true;  // Если все условия выполнены, дерево полное
}

// Вставка элемента в полное бинарное дерево
void insert(CompleteBinaryTree*& root, int value) {
    if (root == nullptr) {
        root = new CompleteBinaryTree(value);
        return;
    }

    if (value < root->value) {
        insert(root->left, value);  // Рекурсивный вызов для левого поддерева
    } else {
        insert(root->right, value);  // Рекурсивный вызов для правого поддерева
    }
}

// Поиск элемента в дереве
bool find(CompleteBinaryTree* root, int value) {
    if (root == nullptr) return false;

    Queue<CompleteBinaryTree*> q;
    q.initialize();
    q.push(root);

    while (!q.is_empty()) {
        CompleteBinaryTree* temp = q.front_elem();
        q.pop();

        if (temp->value == value) {
            q.cleanup();
            return true;
        }

        if (temp->left != nullptr) q.push(temp->left);
        if (temp->right != nullptr) q.push(temp->right);
    }
    q.cleanup();
    return false;
}

// Удаление элемента из дерева
void remove(CompleteBinaryTree*& root, int value) {
    if (root == nullptr) return;

    Queue<CompleteBinaryTree*> q;
    q.initialize();
    q.push(root);
    CompleteBinaryTree* target = nullptr;
    CompleteBinaryTree* last = nullptr;

    while (!q.is_empty()) {
        last = q.front_elem();
        q.pop();

        if (last->value == value) {
            target = last;
        }

        if (last->left) q.push(last->left);
        if (last->right) q.push(last->right);
    }

    if (target) {
        target->value = last->value;

        Queue<CompleteBinaryTree*> delQueue;
        delQueue.initialize();
        delQueue.push(root);

        while (!delQueue.is_empty()) {
            CompleteBinaryTree* temp = delQueue.front_elem();
            delQueue.pop();

            if (temp->left) {
                if (temp->left == last) {
                    delete temp->left;
                    temp->left = nullptr;
                    delQueue.cleanup();
                    q.cleanup();
                    return;
                } else {
                    delQueue.push(temp->left);
                }
            }

            if (temp->right) {
                if (temp->right == last) {
                    delete temp->right;
                    temp->right = nullptr;
                    delQueue.cleanup();
                    q.cleanup();
                    return;
                } else {
                    delQueue.push(temp->right);
                }
            }
        }
        delQueue.cleanup();
    }
    q.cleanup();
}