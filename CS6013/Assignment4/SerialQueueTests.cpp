#include "SerialQueue.hpp"
#include <iostream>
#include <vector>

bool testStatic();
bool testDynamic();

bool testStatic() {
    SerialQueue<int> serialQueue{};
    int* ret = new int;
    bool success = true;

    for (int i = 0; i < 6; i++) {
        serialQueue.enqueue(i);
    }

    if (serialQueue.size() != 6) {
        std::cout << "Static enqueue failed.\n";
        success = false;
    }

    for (int i = 0; i < 6; i++) {
        if (! serialQueue.dequeue(ret)) {
            std::cout << "Static dequeue failed.\n";
            success = false;
        }
    }

    if (serialQueue.dequeue(ret) || serialQueue.size() != 0) {
        std::cout << "Static dequeue failed.\n";
        success = false;
    }

    if (*ret != 5) {
        std::cout << "Static dequeue ret failed.\n";
        success = false;
    }

    delete ret;

    if (success) {
        std::cout << "Static tests passed." << std::endl;
    }

    return success;
}

bool testDynamic() {
    auto* serialQueue = new SerialQueue<int*>;
    int** ret = new int *;
    bool success = true;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            serialQueue->enqueue(new int(i));
        }
    }

    if (serialQueue->size() != 6) {
        std::cout << "Dynamic enqueue failed.\n";
        success = false;
    }

    for (int i = 0; i < 6; i++) {
        if (! serialQueue->dequeue(ret)) {
            std::cout << "Dynamic dequeue failed.\n";
            success = false;
        }
    }

    if (serialQueue->dequeue(ret) || serialQueue->size() != 0) {
        std::cout << "Dynamic dequeue failed.\n";
        success = false;
    }

    if (**ret != 2) {
        std::cout << "Dynamic dequeue ret failed.\n";
        success = false;
    }

    delete ret;
    delete serialQueue;

    if (success) {
        std::cout << "Dynamic tests passed." << std::endl;
    }

    return success;
}

int main(int argc, char** argv) {
    if (argc != 1) {
        std::cerr << "Invalid command." << std::endl;
        exit(1);
    }

    if (testStatic() && testDynamic()) {
        std::cout << "Serial tests passed!" << std::endl;
        return 0;
    }

    return 1;
}