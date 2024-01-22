//
//  NumberRepresentations.cpp
//  NumberRepresentations
//
//  Created by Laura Zhang on 9/7/22.
//

#include "NumberRepresentations.hpp"

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

bool approxEquals(double a, double b, double tolerance) {
    double difference = abs(a - b);
    return (difference <= tolerance);
}

void printFile(const char* file_name) {
    ifstream ins(file_name);
    
    char c;
    int ascii_counter = 0;
    int unicode_counter = 0;

    while(ins >> c) {
        cout << c << endl;
        
        if (c >= 0 && c < 128) {
            ascii_counter++;
        }
        
        else {
            unicode_counter++;
        }
    }
    
    cout << "The number of ASCII is " << ascii_counter;
    cout << ", and the number of Unicode is " << unicode_counter << endl;
}
