#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

struct HashNode {
    string key;
    string value;
    HashNode* next;
};

struct HashTable {
    HashNode** table;  // Указатель на массив указателей
    int size;          // Размер таблицы

    HashTable(int size = 10);
    ~HashTable();

    void initialize();
    int hashFunction(const string& key);
    void insert(const string& key, const string& value);
    string get(const string& key);
    void remove(const string& key);
    void cleanup();
};

#endif
