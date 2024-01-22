#pragma once

template <typename T>
class SerialQueue {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* head;
    Node* tail;
    int size_;

public:
    SerialQueue()
        : head(new Node{T{}, nullptr}), size_(0)
    {
        tail = head;
    }

    void enqueue(const T& x) {
        tail->next = new Node{x, nullptr};
        tail = tail->next;
        size_++;
    }

    bool dequeue(T* ret) {
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

    ~SerialQueue() {
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
