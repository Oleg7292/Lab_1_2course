#include "HashTable.h"

HashTable::HashTable(int size) : size(size) {
    table = new HashNode*[size];
    initialize();
}

HashTable::~HashTable() {
    cleanup();
    delete[] table;
}

void HashTable::initialize() {
    for (int i = 0; i < size; ++i) {
        table[i] = nullptr;
    }
}

int HashTable::hashFunction(const string& key) {
    int hash = 0;
    for (char ch : key) {
        hash += ch;
    }
    return hash % size;
}

void HashTable::insert(const string& key, const string& value) {
    int index = hashFunction(key);
    HashNode* temp = table[index];

    while (temp != nullptr) {
        if (temp->key == key) {
            temp->value = value;  // Обновление значения
            return;
        }
        temp = temp->next;
    }

    HashNode* newNode = new HashNode{key, value, table[index]};
    table[index] = newNode;  // Вставка в начало списка
}

string HashTable::get(const string& key) {
    int index = hashFunction(key);
    HashNode* temp = table[index];

    while (temp != nullptr) {
        if (temp->key == key) {
            return temp->value;
        }
        temp = temp->next;
    }

    throw out_of_range("Key not found");
}

void HashTable::remove(const string& key) {
    int index = hashFunction(key);
    HashNode* temp = table[index];
    HashNode* prev = nullptr;

    while (temp != nullptr && temp->key != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cerr << "Key not foundn";
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
    for (int i = 0; i < size; ++i) {
        HashNode* temp = table[i];
        while (temp != nullptr) {
            HashNode* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        table[i] = nullptr;  // Обнуление указателя
    }
}
