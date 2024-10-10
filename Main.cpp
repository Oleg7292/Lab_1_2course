#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Подключаем все структуры данных
#include "Array.h"
#include "LinkedList.h"
#include "DoublyLinkedList.h"  // Двусвязный список
#include "Stack.h"
#include "Queue.h"
#include "HashTable.h"
#include "CompleteBinaryTree.h"

// Функция для обработки команды
void processCommand(const std::string& command, Array& array, LinkedList& list, DoublyLinkedList& dlist, Stack& stack, Queue& queue, HashTable& ht, CompleteBinaryTree& tree) {
    std::istringstream iss(command);
    std::string action, structure;
    iss >> structure >> action;
    
    if (structure == "M") { // Операции с массивом
        if (action == "PUSH") {
            int value;
            iss >> value;
            array.add(value);
        } else if (action == "GET") {
            int index;
            iss >> index;
            std::cout << "Array element at index " << index << ": " << array.get(index) << std::endl;
        } else if (action == "DEL") {
            int index;
            iss >> index;
            array.removeAt(index);
        }
    }
    else if (structure == "L") { // Операции с односвязным списком
        if (action == "PUSH") {
            int value;
            iss >> value;
            list.push_back(value);
        } else if (action == "DEL") {
            int value;
            iss >> value;
            list.remove(value);
        }
    }
    else if (structure == "DL") { // Операции с двусвязным списком
        if (action == "PUSH_FRONT") {
            int value;
            iss >> value;
            dlist.push_front(value);
        } else if (action == "PUSH_BACK") {
            int value;
            iss >> value;
            dlist.push_back(value);
        } else if (action == "DEL") {
            int value;
            iss >> value;
            dlist.remove(value);
        }
    }
    else if (structure == "S") { // Операции со стеком
        if (action == "PUSH") {
            int value;
            iss >> value;
            stack.push(value);
        } else if (action == "POP") {
            stack.pop();
        }
    }
    else if (structure == "Q") { // Операции с очередью
        if (action == "PUSH") {
            int value;
            iss >> value;
            queue.push(value);
        } else if (action == "POP") {
            queue.pop();
        }
    }
    else if (structure == "H") { // Операции с хэш-таблицей
        if (action == "SET") {
            std::string key;
            int value;
            iss >> key >> value;
            ht.insert(key, value);
        } else if (action == "GET") {
            std::string key;
            iss >> key;
            std::cout << "HashTable value for key " << key << ": " << ht.get(key) << std::endl;
        } else if (action == "DEL") {
            std::string key;
            iss >> key;
            ht.remove(key);
        }
    }
    else if (structure == "T") { // Операции с деревом
        if (action == "INSERT") {
            int value;
            iss >> value;
            tree.insert(value);
        } else if (action == "CHECK_COMPLETE") {
            if (tree.isComplete()) {
                std::cout << "The tree is complete!" << std::endl;
            } else {
                std::cout << "The tree is not complete." << std::endl;
            }
        }
    }
}

// Чтение команд из файла
void processFile(const std::string& filename, Array& array, LinkedList& list, DoublyLinkedList& dlist, Stack& stack, Queue& queue, HashTable& ht, CompleteBinaryTree& tree) {
    std::ifstream file(filename);
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            processCommand(line, array, list, dlist, stack, queue, ht, tree);
        }
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_with_commands>" << std::endl;
        return 1;
    }

    // Инициализация структур данных
    Array array;
    array.initialize();
    
    LinkedList list;
    list.initialize();

    DoublyLinkedList dlist;
    dlist.initialize();

    Stack stack;
    stack.initialize();
    
    Queue queue;
    queue.initialize();

    HashTable ht;
    ht.initialize();

    CompleteBinaryTree tree;
    tree.initialize();

    // Обработка файла с командами
    processFile(argv[1], array, list, dlist, stack, queue, ht, tree);

    // Очистка памяти перед завершением
    array.cleanup();
    list.cleanup();
    dlist.cleanup();
    stack.cleanup();
    queue.cleanup();
    ht.cleanup();
    tree.cleanup();

    return 0;
}
