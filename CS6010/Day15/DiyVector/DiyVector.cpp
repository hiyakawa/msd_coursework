//
//  DiyVector.cpp
//  DiyVector
//
//  Created by Laura Zhang on 9/13/22.
//

#include "DiyVector.hpp"

#include <iostream>

// default constructor
MyVector::MyVector() {
    _size = 0;
    _capacity = 1;
    _data = new int [_capacity];
}

// generate a vector with the given capacity and a size of 0
MyVector::MyVector(const size_t& initialCapacity) {
    _size = 0;
    _capacity = initialCapacity;
    _data = new int [0];
}

// return the appropriate value in the vector
int MyVector::get(const size_t& index) const {
    if (index < _size) {
        return _data[index];
    }
    
    else {
        std::cerr << "Index is beyond range!" << std::endl;
        exit(IndexBeyondRange);
    }
}

void MyVector::set(const size_t& index, const int& newValue) {
    _data[index] = newValue;
}

void MyVector::pushBack(const int& newElement) {
    // make sure the capacity is enough for inserting an element
    growVector();
    
    // insert the new element
    _data[_size] = newElement;
    _size ++;
}

void MyVector::popBack() {
    _size --;
}

void MyVector::growVector() {
    // allocate memory for a temporary array with twice the size
    if (_size >= _capacity) {
        int* temp_array = new int [_size * 2];
        
        // copy the contents to this temp array
        for (int i = 0; i < _size; i++) {
            temp_array[i] = _data[i];
        }

        _capacity *= 2;

        // free up the old chunk of memory
        delete [] _data;

        _data = temp_array;

        // set the pointer to the temp array to nullptr
        temp_array = nullptr;
    }
}

// deallocate any heap memory used by the MyVector object
void MyVector::freeVector() {
    delete [] _data;
    _data = nullptr;
    _size = 0;
    _capacity = 0;
}

size_t MyVector::getSize() const {
    return _size;
}

size_t MyVector::getCapacity() const {
    return _capacity;
}
