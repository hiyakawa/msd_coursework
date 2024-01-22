#pragma once

#include "HashTable.h"

class MyMalloc {
public:
    HashTable hashTable_;

    MyMalloc();

    void* allocate(size_t bytesToAllocate);
    void deallocate(void* ptr);
};
