//
//  STLMyVector.hpp
//  STLMyVector
//
//  Created by Laura Zhang on 9/20/22.
//

#ifndef STLMyVector_hpp
#define STLMyVector_hpp

#include <iostream>
#include <cstddef>

enum Cases {
    IndexBeyondRange = -1,
};

template<typename T>
class MyVector {
private:
    T* _data;
    size_t _capacity, _size;
    
public:
    MyVector();
    MyVector(const MyVector<T>& rhs);
    MyVector(const size_t& initialCapacity);
    ~MyVector();
    
    MyVector<T>& operator=(const MyVector<T>& rhs);
    
    T operator[](const size_t& index) const;
    T& operator[](const size_t& index);
    
    bool operator==(const MyVector<T>& rhs) const;
    bool operator!=(const MyVector<T>& rhs) const;
    
    bool operator<(const MyVector<T>& rhs) const;
    bool operator<=(const MyVector<T>& rhs) const;
    
    bool operator>(const MyVector<T>& rhs) const;
    bool operator>=(const MyVector<T>& rhs) const;
    
    T get(const size_t& index) const;
    void set(const size_t& index, const T& newValue);
    
    void pushBack(const T& newElement);
    void popBack();
    
    void growVector();
    void freeVector();
    
    size_t getSize() const;
    size_t getCapacity() const;
    
    T* begin();
    const T* begin() const;
    T* end();
    const T* end() const;
};

template<typename T>
MyVector<T>::MyVector() {
    _size = 0;
    _capacity = 1;
    _data = new T [_capacity];
}

template<typename T>
MyVector<T>::MyVector(const MyVector<T>& rhs) {
    // avoid memory leak during self assignment
    if (this != & rhs) {
        _size = rhs._size;
        _capacity = rhs._capacity;
        _data = new T [_capacity];
        
        for (size_t i = 0; i < _size; i++) {
            _data[i] = rhs._data[i];
        }
    }
}

template<typename T>
MyVector<T>::MyVector(const size_t& initialCapacity) {
    _size = 0;
    _capacity = initialCapacity;
    _data = new T [0];
}

template<typename T>
MyVector<T>::~MyVector() {
    delete [] _data;
    _data = nullptr;
    _size = 0;
    _capacity = 0;
}

// overload operator=
template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& rhs) {
    // if the two arrays have the same address, skip the copying
    if (this == & rhs) {
        return * this;
    }
    
    // do a deep copy
    _size = rhs._size;
    _capacity = rhs._size;
    
    delete[] _data;
    _data = new T[rhs._capacity];
    
    for (size_t i = 0; i < _size; i++) {
        _data[i] = rhs._data[i];
    }
    
    return * this;
}

// overload operator[] as a const method
template<typename T>
T MyVector<T>::operator[](const size_t& index) const {
    if (index < _size) {
        return _data[index];
    }
    
    else {
        std::cerr << "Index is beyond range!" << std::endl;
        exit(IndexBeyondRange);
    }
}

// overload operator[]
template<typename T>
T& MyVector<T>::operator[](const size_t& index) {
    if (index < _size) {
        return _data[index];
    }
    
    else {
        std::cerr << "Index is beyond range!" << std::endl;
        exit(IndexBeyondRange);
    }
}

// overload operator==
template<typename T>
bool MyVector<T>::operator==(const MyVector<T>& rhs) const {
    if (_size == rhs._size) {
        for (size_t i = 0; i < _size; i++) {
            if (_data[i] != rhs._data[i]) {
                return false;
            }
        }
    }
    
    else {
        return false;
    }
    
    return true;
}

// overload operator!=
template<typename T>
bool MyVector<T>::operator!=(const MyVector<T>& rhs) const {
    return ! operator==(rhs);
}

// overload operator<
template<typename T>
bool MyVector<T>::operator<(const MyVector<T>& rhs) const {
    if (_size == rhs._size) {
        for (size_t i = 0; i < _size; i++) {
            if (_data[i] > rhs._data[i]) {
                return false;
            }
            
            else if (_data[i] < rhs._data[i]) {
                return true;
            }
        }
    }
    
    // if the sizes are not equal, do not compare the two vectors
    return false;
}

// overload operator<=
template<typename T>
bool MyVector<T>::operator<=(const MyVector<T>& rhs) const {
    return (operator==(rhs) || operator<(rhs));
}

// overload operator>
template<typename T>
bool MyVector<T>::operator>(const MyVector<T>& rhs) const {
    return ! operator<=(rhs);
}

// overload operator>=
template<typename T>
bool MyVector<T>::operator>=(const MyVector<T>& rhs) const {
    return ! operator<(rhs);
}

template<typename T>
T MyVector<T>::get(const size_t& index) const {
    if (index < _size) {
        return _data[index];
    }
    
    else {
        std::cerr << "Index is beyond range!" << std::endl;
        exit(IndexBeyondRange);
    }
}

template<typename T>
void MyVector<T>::set(const size_t& index, const T& newValue) {
    _data[index] = newValue;
}

template<typename T>
void MyVector<T>::pushBack(const T& newElement) {
    // make sure the capacity is enough for inserting an element
    growVector();
    
    // insert the new element
    _data[_size] = newElement;
    _size++;
}

template<typename T>
void MyVector<T>::popBack() {
    _size --;
}

template<typename T>
void MyVector<T>::growVector() {
    // allocate memory for a temporary array with twice the size
    if (_size >= _capacity) {
        T* temp_array = new T [_size * 2];
        
        // copy the contents to this temp array
        for (size_t i = 0; i < _size; i++) {
            temp_array[i] = _data[i];
        }
        
        _capacity = 2 * _size;

        delete [] _data;
        _data = temp_array;
        temp_array = nullptr;
    }
}

template<typename T>
size_t MyVector<T>::getSize() const {
    return _size;
}

template<typename T>
size_t MyVector<T>::getCapacity() const {
    return _capacity;
}

template<typename T>
T* MyVector<T>::begin() {
    return _data;
}

template<typename T>
const T* MyVector<T>::begin() const {
    return _data;
}

template<typename T>
T* MyVector<T>::end() {
    return _data + _size;
}

template<typename T>
const T* MyVector<T>::end() const {
    return _data + _size;
}

bool isEvenNum(const int& i);

#endif /* STLMyVector_hpp */
