/*
 * Author: Muyuan Zhang
 *
 * Instructions for how to run the tests + benchmarks
 * Run the main function. This will run testMalloc() and timeMalloc().
 * If it prints "MyMalloc can correctly allocate and deallocate memory.",
 * the MyMalloc class is running correctly.
 * Then it should print how MyMalloc is slower than the standard library malloc.
 * To change the size of test, edit line 36 `TEST_SIZE` in main.cpp
 */

#include "MyAlloc.h"
#include <cstdlib>
#include <iostream>
#include <vector>

void testMalloc() {
    // allocate and deallocate memory
    MyMalloc myMalloc;
    std::vector<void*> ptrs;

    for (int i = 0; i < 100; i++) {
        void* ptr = myMalloc.allocate((rand() % 10) + 1);
        ptrs.push_back(ptr);
    }

    for (void*& curPtr : ptrs){
        myMalloc.deallocate(curPtr);
    }

    std::cout << "MyMalloc can correctly allocate and deallocate memory.";
    std::cout << std::endl << std::endl;
}

void timeMalloc() {
    // compare myAllocator vs the builtin malloc
    MyMalloc myMalloc;
    int TEST_SIZE = 10000;

    std::vector<void*> myMallocPtrs;
    std::vector<void*> ptrs;
    std::vector<size_t> sizes;

    for (int i = 0; i < TEST_SIZE; i++) {
        int* a = new int;
        size_t s = (rand() % 1000) + 1;

        ptrs.push_back(a);
        sizes.push_back(s);
    }

    // record the time using myAllocator
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TEST_SIZE; i++) {
        myMallocPtrs.push_back(myMalloc.allocate(sizes[i]));
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
    int myMallocTime = duration.count();

    // record the time using the builtin malloc
    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TEST_SIZE; i++) {
        ptrs.push_back(malloc(sizes[i]));
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::nanoseconds>(stop - start);
    int mallocTime = duration.count();

    // record the time using myDeAllocator
    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TEST_SIZE; i++) {
        myMalloc.deallocate(myMallocPtrs[i]);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::nanoseconds>(stop - start);
    int myDeallocTime = duration.count();

    // record the time using free()
    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TEST_SIZE; i++) {
        free(ptrs[i]);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::nanoseconds>(stop - start);
    int freeTime = duration.count();

    std::cout << "For " << TEST_SIZE << " times of tests:" << std::endl << std::endl;
    std::cout << "My allocator    : " << myMallocTime  << " ns" << std::endl;
    std::cout << "Builtin malloc(): " << mallocTime    << " ns" << std::endl << std::endl;

    std::cout << "My allocator is " << myMallocTime / mallocTime;
    std::cout << "x slower than the standard library malloc()." << std::endl << std::endl;

    std::cout << "My deallocator  : " << myDeallocTime << " ns" << std::endl;
    std::cout << "Builtin free()  : " << freeTime      << " ns" << std::endl << std::endl;

    std::cout << "My deallocator is " << myDeallocTime / freeTime;
    std::cout << "x slower than the standard library free()." << std::endl;
}

int main() {
    try {
        testMalloc();
        timeMalloc();

        return 0;
    }
    catch (std::exception e) {
        throw e;
    }
}
