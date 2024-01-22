//
//  main.cpp
//  VolumeConvert
//
//  Created by Laura Zhang on 8/23/22.
//  Group member: Laura Zhang (Part 1), Reshma Raghavan (Part 2)
//

#include <iostream>
using namespace std;

int main() {
    cout << "Enter volume in ounces:" << endl;
    float volume_in_ounces = -1;
    cin >> volume_in_ounces;
    
    float cups = 1.0/8;
    float pints = 1.0/16;
    float gallons = 1.0/128;
    float liters = 0.0296;
    float inches = 1.8;
    
    float volume_in_cups = volume_in_ounces * cups;
    float volume_in_pints = volume_in_ounces * pints;
    float volume_in_gallons = volume_in_ounces * gallons;
    float volume_in_liters = volume_in_ounces * liters;
    float volume_in_cubic_inches = volume_in_ounces * inches;
    
    
    cout << "Ounces: " << volume_in_ounces << endl;
    cout << "Cups: " << volume_in_cups << endl;
    cout << "Pints: " << volume_in_pints << endl;
    cout << "Gallons: " << volume_in_gallons << endl;
    cout << "Liters: " << volume_in_liters << endl;
    cout << "Cubic Inches: " << volume_in_cubic_inches << endl;
    
    return 0;
}
