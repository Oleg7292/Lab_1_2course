 #include "HashTable.h"
#include <iostream>
#include <stdexcept>

void HashTable::initialize() {
    for (int i = 0; i < 10; ++i) {
        table[i] = nullptr;
    }
}

int HashTable::hashFunction(const std::string& key) {
    int hash = 0;
    for (char ch : key) {
        hash += ch;
    }
    return hash % 10;
}

void HashTable::insert(const std::string& key, int value) {
    int index = hashFunction(key);
    HashNode* newNode = new HashNode{key, value, nullptr};
    
    if (table[index] == nullptr) {
        table[index] = newNode;
    } else {
        HashNode* temp = table[index];
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int HashTable::get(const std::string& key) {
    int index = hashFunction(key);
    HashNode* temp = table[index];
    
    while (temp != nullptr) {
        if (temp->key == key) {
            return temp->value;
        }
        temp = temp->next;
    }
    
    throw std::out_of_range("Key not found");
}

void HashTable::remove(const std::string& key) {
    int index = hashFunction(key);
    HashNode* temp = table[index];
    HashNode* prev = nullptr;

    while (temp != nullptr && temp->key != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        std::cerr << "Key not found\n";
        return;
    }

    if (prev == nullptr) {
        table[index] = temp->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;
}

void HashTable::cleanup() {
    for (int i = 0; i < 10; ++i) {
        HashNode* temp = table[i];
        while (temp != nullptr) {
            HashNode* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }
}
