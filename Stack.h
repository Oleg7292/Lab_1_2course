#ifndef STACK_H
#define STACK_H

#include <string>

using namespace std;

struct StackNode {  // Переименовано
    string data;
    StackNode* next;  // Указатель на следующий узел
};

struct Stack {
    StackNode* top;  // Указатель на вершину стека

    void initialize();
    void push(const string& value);
    void pop();
    string top_elem() const;
    void cleanup();
};

#endif
