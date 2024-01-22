//
//  final.hpp
//  final
//
//  Created by Laura Zhang on 9/23/22.
//

#ifndef final_hpp
#define final_hpp

#include <cstddef>
#include <cmath>

class MyString{
private:
    char * data;
    size_t size, capacity;
public:
    MyString();
    void pushBack(const char& newElement);
    void growVector();
    char get(int i);
    MyString& operator=(const MyString& rhs);
    MyString operator+(const MyString& rhs) const;
    ~MyString();
};

// Write a function template to compute and return
// the y-th power of a number x. Here, x could be
// any type, but y is always an int.
template<typename T>
T templatizedPower(T x, int y) {
    return std::pow(x, y);
}

#endif /* final_hpp */
