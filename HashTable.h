#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

struct HashNode {
    std::string key;
    int value;
    HashNode* next;
};

struct HashTable {
    HashNode* table[10];

    void initialize();
    int hashFunction(const std::string& key);
    void insert(const std::string& key, int value);
    int get(const std::string& key);
    void remove(const std::string& key);
    void cleanup();
};

#endif
