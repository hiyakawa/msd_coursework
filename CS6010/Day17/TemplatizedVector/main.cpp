//
//  main.cpp
//  TemplatizedVector
//
//  Created by Laura Zhang on 9/16/22.
//  Group members: Muyuan Zhang, Gloria Dukuzeyesu
//

#include "TemplatizedVector.hpp"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main(int argc, const char * argv[]) {
    cout << "===============================" << endl;
    cout << "    tests for MyVector<int>    " << endl;
    cout << "===============================" << endl;
    
    // generate a vector with size = 0 and capacity = 1
    MyVector<int> intVec1;
    
    for (int i = 10; i > 0; i--) {
        intVec1.pushBack(i);
    }
    
    cout << endl << "The elements in intVec1 are:" << endl;
    
    for (size_t i = 0; i < intVec1.getSize(); i++) {
        cout << intVec1[i] << " ";
    }
    
    cout << endl << "intVec1's size is " << intVec1.getSize();
    cout << ", capacity is " << intVec1.getCapacity() << endl << endl;
    
    // call the copy constructor
    MyVector<int> intVec2(intVec1);
    
    cout << "***** tests for copy constructor *****" << endl;
    cout << endl << "The elements in intVec2 are:" << endl;
    
    for (size_t i = 0; i < intVec2.getSize(); i++) {
        cout << intVec2[i] << " ";
    }
    
    cout << endl << "intVec2's size is " << intVec2.getSize();
    cout << ", capacity is " << intVec2.getCapacity() << endl << endl;
    
    MyVector<int> intVec3(1);
    intVec3 = intVec1;
    
    cout << "***** tests for operator=() **********" << endl;
    cout << endl << "The elements in intVec3 are:" << endl;
    
    for (size_t i = 0; i < intVec3.getSize(); i++) {
        cout << intVec3[i] << " ";
    }
    
    cout << endl << "intVec3's size is " << intVec3.getSize();
    cout << ", capacity is " << intVec3.getCapacity() << endl << endl;
    
    // modify the last element of intVec2
    intVec2[intVec2.getSize() - 1] = intVec1[0];
    
    cout << "***** tests for operator[]() *********" << endl;
    cout << endl << "The " << intVec2.getSize() - 1;
    cout << "th element in intVec2 is modified." << endl;
    
    cout << endl << "The elements in intVec2 are:" << endl;
    
    for (size_t i = 0; i < intVec2.getSize(); i++) {
        cout << intVec2[i] << " ";
    }
    
    cout << endl << "intVec2's size is " << intVec2.getSize();
    cout << ", capacity is " << intVec2.getCapacity();
    
    cout << endl << endl << "***** tests for operator==() *********";
    cout << endl << "intVec1 == intVec2? " << (intVec1 == intVec2);
    cout << endl << "intVec1 == intVec3? " << (intVec1 == intVec3);
    
    cout << endl << endl << "***** tests for operator!=() *********";
    cout << endl << "intVec1 != intVec2? " << (intVec1 != intVec2);
    cout << endl << "intVec1 != intVec3? " << (intVec1 != intVec3);
    
    cout << endl << endl << "***** tests for operator<() **********";
    cout << endl << "intVec1 <  intVec2? " << (intVec1 < intVec2);
    cout << endl << "intVec1 <  intVec3? " << (intVec1 < intVec3);
    
    cout << endl << endl << "***** tests for operator<=() *********";
    cout << endl << "intVec1 <= intVec2? " << (intVec1 <= intVec2);
    cout << endl << "intVec2 <= intVec3? " << (intVec2 <= intVec3);
    
    cout << endl << endl << "***** tests for operator>() **********";
    cout << endl << "intVec1 >  intVec2? " << (intVec1 > intVec2);
    cout << endl << "intVec2 >  intVec3? " << (intVec2 > intVec3);
    
    cout << endl << endl << "***** tests for operator>=() *********";
    cout << endl << "intVec1 >= intVec2? " << (intVec1 >= intVec2);
    cout << endl << "intVec2 >= intVec3? " << (intVec2 >= intVec3);
    cout << endl << endl;
    
    cout << "===============================" << endl;
    cout << "   tests for MyVector<double>  " << endl;
    cout << "===============================" << endl;
    
    MyVector<double> dblVec1;
    
    for (double i = 10.1; i > 0; i--) {
        dblVec1.pushBack(i);
    }
    
    cout << endl << "The elements in dblVec1 are:" << endl;
    
    for (size_t i = 0; i < dblVec1.getSize(); i++) {
        cout << dblVec1[i] << " ";
    }
    
    cout << endl << "dblVec1's size is " << dblVec1.getSize();
    cout << ", capacity is " << dblVec1.getCapacity() << endl << endl;
    
    MyVector<double> dblVec2(dblVec1);
    
    cout << "***** tests for copy constructor *****" << endl;
    cout << endl << "The elements in dblVec2 are:" << endl;
    
    for (size_t i = 0; i < dblVec2.getSize(); i++) {
        cout << dblVec2[i] << " ";
    }
    
    cout << endl << "dblVec2's size is " << dblVec2.getSize();
    cout << ", capacity is " << dblVec2.getCapacity() << endl << endl;
    
    MyVector<double> dblVec3 = dblVec1;
    
    cout << "***** tests for operator=() **********" << endl;
    cout << endl << "The elements in dblVec3 are:" << endl;
    
    for (size_t i = 0; i < dblVec3.getSize(); i++) {
        cout << dblVec3[i] << " ";
    }
    
    cout << endl << "dblVec3's size is " << dblVec3.getSize();
    cout << ", capacity is " << dblVec3.getCapacity() << endl << endl;

    // modify the last element of dblVec2
    dblVec2[dblVec2.getSize() - 1] = dblVec1[0];
    
    cout << "***** tests for operator[]() *********" << endl;
    cout << endl << "The " << dblVec2.getSize() - 1;
    cout << "th element in dblVec2 is modified." << endl;
    
    cout << endl << "The elements in dblVec2 are:" << endl;
    
    for (size_t i = 0; i < dblVec2.getSize(); i++) {
        cout << dblVec2[i] << " ";
    }
    
    cout << endl << "dblVec2's size is " << dblVec2.getSize();
    cout << ", capacity is " << dblVec2.getCapacity();
    
    cout << endl << endl << "***** tests for operator==() *********";
    cout << endl << "dblVec1 == dblVec2? " << (dblVec1 == dblVec2);
    cout << endl << "dblVec1 == dblVec3? " << (dblVec1 == dblVec3);
    
    cout << endl << endl << "***** tests for operator!=() *********";
    cout << endl << "dblVec1 != dblVec2? " << (dblVec1 != dblVec2);
    cout << endl << "dblVec1 != dblVec3? " << (dblVec1 != dblVec3);
    
    cout << endl << endl << "***** tests for operator<() **********";
    cout << endl << "dblVec1 <  dblVec2? " << (dblVec1 < dblVec2);
    cout << endl << "dblVec1 <  dblVec3? " << (dblVec1 < dblVec3);
    
    cout << endl << endl << "***** tests for operator<=() *********";
    cout << endl << "dblVec1 <= dblVec2? " << (dblVec1 <= dblVec2);
    cout << endl << "dblVec2 <= dblVec3? " << (dblVec2 <= dblVec3);
    
    cout << endl << endl << "***** tests for operator>() **********";
    cout << endl << "dblVec1 >  dblVec2? " << (dblVec1 > dblVec2);
    cout << endl << "dblVec2 >  dblVec3? " << (dblVec2 > dblVec3);
    
    cout << endl << endl << "***** tests for operator>=() *********";
    cout << endl << "dblVec1 >= dblVec2? " << (dblVec1 >= dblVec2);
    cout << endl << "dblVec2 >= dblVec3? " << (dblVec2 >= dblVec3);
    cout << endl << endl;
    
    
    cout << "===============================" << endl;
    cout << "   tests for MyVector<string>  " << endl;
    cout << "===============================" << endl;
    
    MyVector<string> strVec1;
    
    strVec1.pushBack("abc");
    strVec1.pushBack("d");
    strVec1.pushBack("ef");
    
    cout << endl << "The elements in strVec1 are:" << endl;
    
    for (size_t i = 0; i < strVec1.getSize(); i++) {
        cout << strVec1[i] << " ";
    }
    
    cout << endl << "strVec1's size is " << strVec1.getSize();
    cout << ", capacity is " << strVec1.getCapacity() << endl << endl;
    
    MyVector<string> strVec2(strVec1);
    
    cout << "***** tests for copy constructor *****" << endl;
    cout << endl << "The elements in strVec2 are:" << endl;
    
    for (size_t i = 0; i < strVec2.getSize(); i++) {
        cout << strVec2[i] << " ";
    }
    
    cout << endl << "strVec2's size is " << strVec2.getSize();
    cout << ", capacity is " << strVec2.getCapacity() << endl << endl;
    
    MyVector<string> strVec3 = strVec1;
    
    cout << "***** tests for operator=() **********" << endl;
    cout << endl << "The elements in strVec3 are:" << endl;
    
    for (size_t i = 0; i < strVec3.getSize(); i++) {
        cout << strVec3[i] << " ";
    }
    
    cout << endl << "strVec3's size is " << strVec3.getSize();
    cout << ", capacity is " << strVec3.getCapacity() << endl << endl;
    
    // modify the last element of strVec2
    strVec2[strVec2.getSize() - 1] = strVec1[0];
    
    cout << "***** tests for operator[]() *********" << endl;
    cout << endl << "The " << strVec2.getSize() - 1;
    cout << "th element in strVec2 is modified." << endl;
    
    cout << endl << "The elements in strVec2 are:" << endl;
    
    for (size_t i = 0; i < strVec2.getSize(); i++) {
        cout << strVec2[i] << " ";
    }
    
    cout << endl << "strVec2's size is " << strVec2.getSize();
    cout << ", capacity is " << strVec2.getCapacity();
    
    cout << endl << endl << "***** tests for operator==() *********";
    cout << endl << "strVec1 == strVec2? " << (strVec1 == strVec2);
    cout << endl << "strVec1 == strVec3? " << (strVec1 == strVec3);
    
    cout << endl << endl << "***** tests for operator!=() *********";
    cout << endl << "strVec1 != strVec2? " << (strVec1 != strVec2);
    cout << endl << "strVec1 != strVec3? " << (strVec1 != strVec3);
    
    cout << endl << endl << "***** tests for operator<() **********";
    cout << endl << "strVec1 <  strVec2? " << (strVec1 < strVec2);
    cout << endl << "strVec1 <  strVec3? " << (strVec1 < strVec3);
    
    cout << endl << endl << "***** tests for operator<=() *********";
    cout << endl << "strVec1 <= strVec2? " << (strVec1 <= strVec2);
    cout << endl << "strVec2 <= strVec3? " << (strVec2 <= strVec3);
    
    cout << endl << endl << "***** tests for operator>() **********";
    cout << endl << "strVec1 >  strVec2? " << (strVec1 > strVec2);
    cout << endl << "strVec2 >  strVec3? " << (strVec2 > strVec3);
    
    cout << endl << endl << "***** tests for operator>=() *********";
    cout << endl << "strVec1 >= strVec2? " << (strVec1 >= strVec2);
    cout << endl << "strVec2 >= strVec3? " << (strVec2 >= strVec3);
    cout << endl << endl;
    
    
    cout << "===============================" << endl;
    cout << "   tests for MyVector<char>    " << endl;
    cout << "===============================" << endl;
    
    MyVector<char> charVec1;
    
    charVec1.pushBack('c');
    charVec1.pushBack('a');
    charVec1.pushBack('e');
    charVec1.pushBack('q');
    charVec1.pushBack('1');
    
    cout << endl << "The elements in charVec1 are:" << endl;
    
    for (size_t i = 0; i < charVec1.getSize(); i++) {
        cout << charVec1[i] << " ";
    }
    
    cout << endl << "charVec1's size is " << charVec1.getSize();
    cout << ", capacity is " << charVec1.getCapacity() << endl << endl;
    
    MyVector<char> charVec2(charVec1);
    
    cout << "***** tests for copy constructor *****" << endl;
    cout << endl << "The elements in charVec2 are:" << endl;
    
    for (size_t i = 0; i < charVec2.getSize(); i++) {
        cout << charVec2[i] << " ";
    }
    
    cout << endl << "charVec2's size is " << charVec2.getSize();
    cout << ", capacity is " << charVec2.getCapacity() << endl << endl;
    
    MyVector<char> charVec3 = charVec1;
    
    cout << "***** tests for operator=() **********" << endl;
    cout << endl << "The elements in charVec3 are: " << endl;
    
    for (size_t i = 0; i < charVec3.getSize(); i++) {
        cout << charVec3[i] << " ";
    }
    
    cout << endl << "charVec3's size is " << charVec3.getSize();
    cout << ", capacity is " << charVec3.getCapacity() << endl << endl;
    
    // modify the last element of charVec2
    charVec2[charVec2.getSize() - 1] = charVec1[0];
    
    cout << "***** tests for operator[]() *********" << endl;
    cout << endl << "The " << charVec2.getSize() - 1;
    cout << "th element in charVec2 is modified." << endl;

    cout << endl << "The elements in charVec2 are:" << endl;
    
    for (size_t i = 0; i < charVec2.getSize(); i++) {
        cout << charVec2[i] << " ";
    }
    
    cout << endl << "charVec2's size is " << charVec2.getSize();
    cout << ", capacity is " << charVec2.getCapacity();
    
    cout << endl << endl << "***** tests for operator==() *********";
    cout << endl << "charVec1 == charVec2? " << (charVec1 == charVec2);
    cout << endl << "charVec1 == charVec3? " << (charVec1 == charVec3);

    cout << endl << endl << "***** tests for operator!=() *********";
    cout << endl << "charVec1 != charVec2? " << (charVec1 != charVec2);
    cout << endl << "charVec1 != charVec3? " << (charVec1 != charVec3);

    cout << endl << endl << "***** tests for operator<() **********";
    cout << endl << "charVec1 <  charVec2? " << (charVec1 < charVec2);
    cout << endl << "charVec1 <  charVec3? " << (charVec1 < charVec3);

    cout << endl << endl << "***** tests for operator<=() *********";
    cout << endl << "charVec1 <= charVec2? " << (charVec1 <= charVec2);
    cout << endl << "charVec2 <= charVec3? " << (charVec2 <= charVec3);

    cout << endl << endl << "***** tests for operator>() **********";
    cout << endl << "charVec1 >  charVec2? " << (charVec1 > charVec2);
    cout << endl << "charVec2 >  charVec3? " << (charVec2 > charVec3);

    cout << endl << endl << "***** tests for operator>=() *********";
    cout << endl << "charVec1 >= charVec2? " << (charVec1 >= charVec2);
    cout << endl << "charVec2 >= charVec3? " << (charVec2 >= charVec3);
    cout << endl << endl;
    
    return 0;
}
