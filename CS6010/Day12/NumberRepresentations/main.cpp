//
//  main.cpp
//  NumberRepresentations
//
//  Created by Laura Zhang on 9/7/22.
//

#include "NumberRepresentations.hpp"

#include <iostream>
#include <iomanip>
#include <cstdint>

using namespace std;

int main(int argc, const char * argv[]) {
    // Part 1
    char c = '1';
    cout << "size of char: " << sizeof(c) << endl;
    // size of char is 1
    
    int i = 1;
    cout << "size of int: " << sizeof(i) << endl;
    // size of int is 4
    
    int a[] = { 7, 2, -56, 32, 1, 7, -2, 7 };
    cout << "size of array of 8 ints: " << sizeof(a) << endl;
    // size of a is 32 because each int takes 4 bytes and there are 8 of them
    
    int8_t i_8 = 1;
    int16_t i_16 = 1;
    uint8_t u_i_8 = 1;
    uint16_t u_i_16 = 1;
    
    cout << "size of int8_t: " << sizeof(i_8) << endl;
    cout << "size of int16_t: " << sizeof(i_16) << endl;
    cout << "size of uint8_t: " << sizeof(u_i_8) << endl;
    cout << "size of uint16_t: " << sizeof(u_i_16) << endl;
    // The number indicates the number of bits.
    // So int8_t and uint8_t take 1 byte, while int16_t and uint16_t take 2 bytes.
    
    uint8_t min_uint8_t = 0x0;
    uint8_t max_uint8_t = 0xFF;
    uint16_t min_uint16_t = 0x0;
    uint16_t max_uint16_t = 0xFFFF;
    uint64_t min_uint64_t = 0X0;
    uint64_t max_uint64_t = 0xFFFFFFFFFFFFFFFF;                 // 2^64 = 16^16
    
    cout << +min_uint8_t << ", " << +max_uint8_t << endl;       // 0, 255
    cout << +min_uint16_t << ", " << +max_uint16_t << endl;     // 0, 65535
    cout << +min_uint64_t << ", " << +max_uint64_t << endl;     // 0, 18446744073709551615
    
    int8_t min_int8_t = -0x80;
    int8_t max_int8_t = 0x7F;
    int16_t min_int16_t = -0x8000;
    int16_t max_int16_t = 0x7FFF;
    int64_t min_int64_t = 0X8000000000000000;
    int64_t max_int64_t = 0x7FFFFFFFFFFFFFFF;
    
    cout << +min_int8_t << ", " << +max_int8_t << endl;         // -128, 127
    cout << +min_int16_t << ", " << +max_int16_t << endl;       // -32768, 32767
    cout << +min_int64_t << ", " << +max_int64_t << endl;       // -9223372036854775808, 9223372036854775807
    
    cout << +(max_int8_t + 1) << endl;                          // 128
    // max plus 1, returns the absolute value of it
    
    cout << +(min_int8_t - 1) << endl;                          // -129
    // returns the exact value of min minus 1
    
    // Part 2
    double point_one = 0.1;
    double point_two = 0.2;
    double point_three = 0.3;
    double point_one_plus_two = point_one + point_two;
    
    cout << setprecision(18) << point_one_plus_two << endl;     // print numbers to 18 digits of accuracy
    cout << setprecision(18) << point_three << endl;
    
    // assert(point_one + point_two == point_three);
    
    // test approxEquals()
    double higher_tolerance = 1e-16;                            // should return true
    double lower_tolerance = 1e-18;                             // should return false
    
    cout << approxEquals(point_one_plus_two, point_three, higher_tolerance) << endl;
    cout << approxEquals(point_one_plus_two, point_three, lower_tolerance) << endl;
    
    // Part 3
    printFile("UTF-8-demo.txt");
    // The number of ASCII is 1636, and the number of Unicode is 10192.
    // ASCII is printed in a readble form and Unicode is garbled.
    
    return 0;
}
