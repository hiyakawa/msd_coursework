//
//  main.cpp
//  NumberConverter
//
//  Created by Laura Zhang on 9/6/22.
//  Group members: Muyuan Zhang, Levi Neely, Lydia Yuan, Lauryn C.
//

#include "NumberConverter.hpp"

#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
    // Part 1 unit tests
    assert(stringToInt("99", 10) == 99);
    
    assert(stringToInt("100", 2) == 4);
    assert(stringToInt("10001", 2) == 17);
    assert(stringToInt("100010", 2) == 34);
    assert(stringToInt("11000000", 2) == 192);
    assert(stringToInt("11111111", 2) == 255);
    assert(stringToInt("-11111", 2) == -31);        // should handle negative numbers
    
    assert(stringToInt("A", 16) == 10);
    assert(stringToInt("C0", 16) == 192);
    assert(stringToInt("FF", 16) == 255);
    assert(stringToInt("BEEF", 16) == 48879);
    assert(stringToInt("F00D", 16) == 61453);
    assert(stringToInt("ff", 16) == 255);           // should handle lower-case letters
    
    cout << stringToInt("1*846", 10);               // should handle invalid symbols
    
    // Part 2 unit tests
    assert(intToDecimalString(10) == "10");
    assert(intToDecimalString(-10) == "-10");       // should handle negative numbers
    assert(intToDecimalString(0) == "0");           // should handle zero
    
    assert(intToBinaryString(12) == "1100");
    assert(intToBinaryString(63) == "111111");
    assert(intToBinaryString(100) == "1100100");
    assert(intToBinaryString(127) == "1111111");
    assert(intToBinaryString(254) == "11111110");
    assert(intToBinaryString(-10) == "-1010");
    assert(intToBinaryString(0) == "0");
    
    assert(intToHexadecimalString(12) == "C");
    assert(intToHexadecimalString(63) == "3F");
    assert(intToHexadecimalString(100) == "64");
    assert(intToHexadecimalString(127) == "7F");
    assert(intToHexadecimalString(254) == "FE");
    assert(intToHexadecimalString(-10) == "-A");
    assert(intToHexadecimalString(0) == "0");
    
    return 0;
}
