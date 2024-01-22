//
//  main.cpp
//  RomanNumerals
//
//  Created by Laura Zhang on 8/25/22.
//

#include <iostream>
#include <string>

using namespace std;

int main() {
    // prompt the user to input a number
    cout << "Enter decimal number:" << endl;
    int input_num = -1;
    cin >> input_num;
    
    string roman_numeral = "";
    
    int m_to_int = 1000;
    int cm_to_int = 900;
    int d_to_int = 500;
    int cd_to_int = 400;
    int c_to_int = 100;
    int xc_to_int = 90;
    int l_to_int = 50;
    int xl_to_int = 40;
    int x_to_int = 10;
    int ix_to_int = 9;
    int v_to_int = 5;
    int iv_to_int = 4;
    int i_to_int = 1;
    
    // refuse non-positive input numbers
    if (input_num <= 0) {
        cout << "Invalid input" << endl;
    }
    
    else {
        // "M" if the remaining number is >= 1000
        while (input_num >= m_to_int) {
            roman_numeral += "M";
            input_num -= m_to_int;
        }
        
        // "CM" if the remaining number is >= 900
        while (input_num >= cm_to_int) {
            roman_numeral += "CM";
            input_num -= cm_to_int;
        }
        
        // "D" if the remaining number is >= 500
        while (input_num >= d_to_int) {
            roman_numeral += "D";
            input_num -= d_to_int;
        }
        
        // "CD" if the remaining number is >= 400
        while (input_num >= cd_to_int) {
            roman_numeral += "CD";
            input_num -= cd_to_int;
        }
        
        // "C" if the remaining number is >= 100
        while (input_num >= c_to_int)
        {
            roman_numeral += "C";
            input_num -= c_to_int;
        }
        
        // "XC" if the remaining number is >= 90
        while (input_num >= xc_to_int) {
            roman_numeral += "XC";
            input_num -= xc_to_int;
        }
        
        // "L" if the remaining number is >= 50
        while (input_num >= l_to_int) {
            roman_numeral += "L";
            input_num -= l_to_int;
        }
        
        // "XL" if the remaining number is >= 40
        while (input_num >= xl_to_int) {
            roman_numeral += "XL";
            input_num -= xl_to_int;
        }
        
        // "X" if the remaining number is >= 10
        while (input_num >= x_to_int) {
            roman_numeral += "X";
            input_num -= x_to_int;
        }
        
        // "IX" if the remaining number is >= 9
        while (input_num >= ix_to_int) {
            roman_numeral += "IX";
            input_num -= ix_to_int;
        }
        
        // "V" if the remaining number is >= 5
        while (input_num >= v_to_int) {
            roman_numeral += "V";
            input_num -= v_to_int;
        }
        
        // "IV" if the remaining number is >= 4
        while (input_num >= iv_to_int) {
            roman_numeral += "IV";
            input_num -= iv_to_int;
        }
        
        // "I" if the remaining number is >= 1
        while (input_num >= i_to_int) {
            roman_numeral += "I";
            input_num -= i_to_int;
        }
        
        // print the result
        cout << "Roman numeral version:" << endl << roman_numeral << endl;
    }
    
    return 0;
}
