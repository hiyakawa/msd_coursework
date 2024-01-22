#pragma once

#include <cstdio>

class HashNode {
public:
    void* ptr_;
    size_t size_;

    HashNode();
};

class HashTable {
public:
    int size_;
    int capacity_;
    HashNode* hashTable_;

    HashTable();
    ~HashTable();

    bool insert(void* ptr, size_t memSize);
    bool remove(void* ptr);
    size_t search(void* ptr);

private:
    void growHashTable();
    int hash(void* ptr) const;
};
