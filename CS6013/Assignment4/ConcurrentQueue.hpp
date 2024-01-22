#pragma once

#include <iostream>

template <typename T>
class ConcurrentQueue {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* head;
    Node* tail;
    int size_;

    std::mutex tailLock, headLock;

public:
    ConcurrentQueue()
        : head(new Node{T{}, nullptr}), size_(0)
    {
        tail = head;
    }

    void enqueue(const T& x) {
        std::lock_guard<std::mutex> lock(tailLock);

        tail->next = new Node{x, nullptr};
        tail = tail->next;
        size_++;
    }

    bool dequeue(T* ret) {
        std::lock_guard<std::mutex> lock(headLock);

        Node* temp = head;

        if (temp->next == nullptr) {
            return false;
        }

        *ret = temp->next->data;
        head = temp->next;
        size_--;
        delete temp;

        return true;
    }

    ~ConcurrentQueue() {
        while (head) {
            Node* temp = head->next;
            delete head;
            head = temp;
        }
    }

    int size() const {
        return size_;
    }
};
