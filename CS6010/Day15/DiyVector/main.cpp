//
//  main.cpp
//  DiyVector
//
//  Created by Laura Zhang on 9/13/22.
//

#include "DiyVector.hpp"

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, const char * argv[]) {
    // call the default constructor
    // should generate a vector with size = 0 and capacity = 1
    MyVector myVec1;
    
    cout << "==============tests for constructors==============" << endl;
    cout << "myVec1's size is " << myVec1.getSize() << endl;
    cout << "myVec1's capacity is " << myVec1.getCapacity() << endl;
    
    // call the default constructor
    // should generate a vector with size = 0 and capacity = 5
    MyVector myVec2(5);
    
    cout << endl << "myVec2's size is " << myVec2.getSize() << endl;
    cout << "myVec2's capacity is " << myVec2.getCapacity() << endl;
    
    cout << endl << "==============tests for pushBack()==============" << endl;
    
    for (int i = 0; i < 11; i++) {
        myVec2.pushBack(i);
        cout << i + 1 << " elements are inserted. myVec2's size is " << myVec2.getSize();
        cout << ", capacity is " << myVec2.getCapacity() << endl;
    }
    
    cout << endl << "==============tests for popBack()==============" << endl;
    
    for (int i = 0; i < 5; i++) {
        myVec2.popBack();
        cout << i + 1 << " elements are deleted. myVec2's size is " << myVec2.getSize();
        cout << ", capacity is " << myVec2.getCapacity() << endl;
    }
    
    cout << endl << "==============tests for get() and set()==============" << endl;
    
    cout << "The 3rd element is " << myVec2.get(3) << endl;
    myVec2.set(3, 100);
    cout << "The 3rd element is modified to " << myVec2.get(3) << endl;
    
    cout << endl << "==============tests for freeVector()==============" << endl;
    
    myVec2.freeVector();
    cout << "The vector is deleted! myVec2's size is " << myVec2.getSize();
    cout << ", capacity is " << myVec2.getCapacity() << endl;
    
    return 0;
}
