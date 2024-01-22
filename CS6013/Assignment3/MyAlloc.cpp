#include "MyAlloc.h"
#include <cstdlib>
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>

MyMalloc::MyMalloc() {
    hashTable_ = HashTable();
}

void* MyMalloc::allocate(size_t bytesToAllocate) {
    // allocate memory with mmap
    void* ptr = mmap(nullptr, bytesToAllocate, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);

    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // insert the returned pointer and the allocation size in the hash table
    hashTable_.insert(ptr, (bytesToAllocate % getpagesize()));

    return ptr;
}

void MyMalloc::deallocate(void* ptr) {
    size_t len = hashTable_.search(ptr);

    if (munmap(ptr, len) != 0) {
        perror("deallocate");
        exit(1);
    }

    // remove the returned pointer from the hash table
    hashTable_.remove(ptr);
}
