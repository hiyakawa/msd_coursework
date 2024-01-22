#include "HashTable.h"
#include <cstdlib>
#include <iostream>
#include <sys/mman.h>

HashNode::HashNode() {
    size_ = 0;
    ptr_ = nullptr;
}

HashTable::HashTable() {
    size_ = 0;
    capacity_ = 10000;
    hashTable_ = (HashNode*) mmap(nullptr, capacity_ * sizeof(HashNode), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);

    if (hashTable_ == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
}

HashTable::~HashTable() {
    size_ = 0;
    capacity_ = 0;
    hashTable_ = nullptr;
}

bool HashTable::insert(void* ptr, size_t memSize) {
    int hashIndex = hash(ptr);

    while (hashTable_[hashIndex].ptr_ != nullptr) {
        if (hashTable_[hashIndex].ptr_ == ptr) {
            return false;
        }

        hashIndex++;
        hashIndex %= capacity_;
    }

    size_++;
    hashTable_[hashIndex].ptr_ = ptr;
    hashTable_[hashIndex].size_ = memSize;
    growHashTable();

    return true;
}

bool HashTable::remove(void* ptr) {
    int hashIndex = hash(ptr);
    int count = 0;

    while (hashTable_[hashIndex].ptr_ != ptr) {
        hashIndex++;
        count++;

        if (count > capacity_) {
            return false;
        }

        hashIndex %= capacity_;
    }

    hashTable_[hashIndex].ptr_ = nullptr;
    hashTable_[hashIndex].size_ = 0;
    size_--;

    return true;
}

size_t HashTable::search(void* ptr) {
    int hashIndex = hash(ptr);
    int count = 0;

    while (hashTable_[hashIndex].ptr_ != ptr) {
        hashIndex++;
        count++;

        if (count > capacity_) {
            return 0;
        }

        hashIndex %= capacity_;
    }

    return hashTable_[hashIndex].size_;
}

void HashTable::growHashTable() {
    if (size_ > capacity_ / 2) {
        int originalCapacity = capacity_;
        HashNode* originalHashTable = hashTable_;
        capacity_ *= 2;

        HashNode* tempHashNode = (HashNode*) mmap(nullptr, capacity_ * sizeof(HashNode), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);

        if (tempHashNode == MAP_FAILED) {
            perror("mmap");
            exit(1);
        }

        hashTable_ = tempHashNode;
        size_ = 0;

        for (int i = 0; i < originalCapacity; ++i) {
            if (originalHashTable[i].ptr_ != nullptr) {
                insert(originalHashTable[i].ptr_, originalHashTable[i].size_);
            }
        }
    }
}

int HashTable::hash(void* ptr) const {
    // implements djb2 algorithm
    // reference: <a href="http://www.cse.yorku.ca/~oz/hash.html">...</a>
    int hash = 5381;
    hash = hash * 33 + (size_t) ptr;

    return abs(hash) % capacity_;
}
