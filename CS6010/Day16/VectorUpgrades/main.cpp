//
//  main.cpp
//  VectorUpgrades
//
//  Created by Laura Zhang on 9/14/22.
//

#include "VectorUpgrades.hpp"

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, const char * argv[]) {
    // call the default constructor
    // should generate a vector with size = 0 and capacity = 1
    MyVector myVec1;
    
    for (int i = 10; i > 0; i--) {
        myVec1.pushBack(i);
    }
    
    // call the copy constructor
    MyVector myVec2(myVec1);
    
    cout << "============== tests for copy constructor ==============";
    cout << endl << "The elements in myVec2 are: ";
    
    for (size_t i = 0; i < myVec2.getSize(); i++) {
        cout << myVec2[i] << " ";
    }
    
    cout << endl << "myVec2's size is " << myVec2.getSize() << endl;
    cout << "myVec2's capacity is " << myVec2.getCapacity() << endl << endl;
    
    MyVector myVec3 = myVec1;
    
    cout << "============== tests for operator=() ==============";
    cout << endl << "The elements in myVec3 are: ";
    
    for (size_t i = 0; i < myVec3.getSize(); i++) {
        cout << myVec3[i] << " ";
    }
    
    cout << endl << "myVec3's size is " << myVec3.getSize() << endl;
    cout << "myVec3's capacity is " << myVec3.getCapacity() << endl << endl;
    
    // modify the first element of myVec2
    myVec2[9] = myVec1[0];
    
    cout << "============== tests for operator[]() ==============";
    cout << endl << "The elements in myVec1 are: ";
    
    for (size_t i = 0; i < myVec1.getSize(); i++) {
        cout << myVec1[i] << " ";
    }
    
    cout << endl << "myVec1's size is " << myVec1.getSize() << endl;
    cout << "myVec1's capacity is " << myVec1.getCapacity() << endl;
    
    cout << endl << "The elements in myVec2 are: ";
    
    for (size_t i = 0; i < myVec2.getSize(); i++) {
        cout << myVec2[i] << " ";
    }
    
    cout << endl << "myVec2's size is " << myVec2.getSize() << endl;
    cout << "myVec2's capacity is " << myVec2.getCapacity() << endl << endl;
    
    cout << "============== tests for operator==() ==============";
    cout << endl << (myVec1 == myVec2) << ", " << (myVec1 == myVec3) << endl << endl;
    
    cout << "============== tests for operator!=() ==============";
    cout << endl << (myVec1 != myVec2) << ", " << (myVec1 != myVec3) << endl << endl;
    
    cout << "============== tests for operator<() ==============";
    cout << endl << (myVec1 < myVec2) << ", " << (myVec1 < myVec3) << endl << endl;
    
    cout << "============== tests for operator<=() ==============";
    cout << endl << (myVec1 <= myVec2) << ", " << (myVec2 <= myVec3) << endl << endl;
    
    cout << "============== tests for operator>() ==============";
    cout << endl << (myVec1 > myVec2) << ", " << (myVec2 > myVec3) << endl << endl;
    
    cout << "============== tests for operator>=() ==============";
    cout << endl << (myVec1 >= myVec2) << ", " << (myVec2 >= myVec3) << endl << endl;
    
    // modify the 11st element of myVec2 (out of the range of index)
    // which should cause an exit and print out an error message
    myVec2[11] = myVec1[0];
    
    return 0;
}
