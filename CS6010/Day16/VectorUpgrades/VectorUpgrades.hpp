//
//  VectorUpgrades.hpp
//  VectorUpgrades
//
//  Created by Laura Zhang on 9/14/22.
//

#ifndef VectorUpgrades_hpp
#define VectorUpgrades_hpp

#include <cstddef>

class MyVector {
private:
    int* _data;
    size_t _capacity, _size;
    
public:
    MyVector();
    MyVector(const MyVector& rhs);
    MyVector(const size_t& initialCapacity);
    ~MyVector();
    
    MyVector& operator=(const MyVector& rhs);
    
    int operator[](const size_t& index) const;
    int& operator[](const size_t& index);
    
    bool operator==(const MyVector& rhs) const;
    bool operator!=(const MyVector& rhs) const;
    
    bool operator<(const MyVector& rhs) const;
    bool operator<=(const MyVector& rhs) const;
    
    bool operator>(const MyVector& rhs) const;
    bool operator>=(const MyVector& rhs) const;
    
    int get(const size_t& index) const;
    void set(const size_t& index, const int& newValue);
    
    void pushBack(const int& newElement);
    void popBack();
    
    void growVector();
    
    size_t getSize() const;
    size_t getCapacity() const;
};

enum Cases {
    IndexBeyondRange = -1,
};

#endif /* VectorUpgrades_hpp */
