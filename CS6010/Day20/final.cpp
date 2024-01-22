//
//  final.cpp
//  final
//
//  Created by Laura Zhang on 9/23/22.
//

#include "final.hpp"

#include <iostream>

using namespace std;

MyString::MyString() {
    size = 0;
    capacity = 1;
    data = new char [capacity];
}

MyString& MyString::operator=(const MyString& rhs) {
    if (this == & rhs) {
        return * this;
    }

    size = rhs.size;
    capacity = rhs.size;
    
    for (size_t i = 0; i < size; i++) {
        data[i] = rhs.data[i];
    }
    
    return * this;
}

MyString::~MyString() {
    delete [] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}

MyString MyString::operator+(const MyString& rhs) const {
    MyString temp_string;
    temp_string.size = size + rhs.size;
    temp_string.capacity = 2 * (size + rhs.size);
    temp_string.data = new char [size + rhs.size];

    for (size_t i = 0; i < size; i++) {
        temp_string.data[i] = data[i];
    }

    for (size_t j = size; j < size + rhs.size; j++) {
        temp_string.data[j] = rhs.data[j - size];
    }
    
    return temp_string;
}

void MyString::pushBack(const char& newElement) {
    // make sure the capacity is enough for inserting an element
    growVector();
    
    // insert the new element
    data[size] = newElement;
    size++;
}

void MyString::growVector() {
    if (size >= capacity) {
        char* temp_array = new char [size * 2];
        
        // copy the contents to this temp array
        for (size_t i = 0; i < size; i++) {
            temp_array[i] = data[i];
        }
        
        capacity = 2 * size;

        delete [] data;
        data = temp_array;
        temp_array = nullptr;
    }
}

char MyString::get(int i) {
    return data[i];
}
