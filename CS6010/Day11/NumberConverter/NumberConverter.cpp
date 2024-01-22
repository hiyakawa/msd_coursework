//
//  NumberConverter.cpp
//  NumberConverter
//
//  Created by Laura Zhang on 9/6/22.
//  Group members: Muyuan Zhang, Levi Neely, Lydia Yuan, Lauryn C.
//

#include "NumberConverter.hpp"

#include <iostream>
#include <cctype>
#include <math.h>

using namespace std;

int stringToInt(const string num, int base) {
    int begin_digit = int (num[0] == '-');                      // if the input number is negative, skip the dash mark when execute the loop and begin with the 1st digit instead of the 0th
    int result_num = 0;                                         // stores the converted result as a decimal number
    
    for (int i = begin_digit; i < (int) num.length(); i++) {    // for each digit in the input number
        char cur_char = num[i];                                 // get the current char
        int numeric_value = 0;
        
        if (isNumeric(cur_char)) {
            numeric_value = cur_char - '0';                     // convert the current char into integer
        }
        
        else if (isValidLetter(cur_char)) {
            cur_char = tolower(cur_char);                       // make all the letter into lower-case
            numeric_value = cur_char - 'a' + 10;                // convert the current char to integer
        }
        
        else {                                                  // if the char is not a number or a valid letter
            cerr << "Invalid input: " << cur_char << endl;      // print the current char and an error message
            exit(invalid_input);                                // exit the program
        }
        
        int cur_index = (int) num.length() - 1 - i;             // get the current index (from right to left)
        int cur_digit_to_decimal = numeric_value * pow(base, cur_index);
        
        result_num += cur_digit_to_decimal;                     // add up to the result
    }
    
    if (begin_digit == 1) {                                     // if the input number is negative
        result_num = 0 - result_num;                            // negate it
    }
    
    return result_num;
}

bool isNumeric(char c) {                                        // check if a char is a number by its ASCII
    if (c > 47 && c < 58) {
        return true;
    }
    
    return false;
}

bool isValidLetter(char c) {                                    // check if a char is a letter between 'a' and 'f'
    if ((c > 64 && c < 71) || (c > 96 && c < 103)) {            // both lower and upper-case are considered valid
        return true;
    }
    
    return false;
}

string intToDecimalString(int num) {                            // convert decimal int to decimal string
    int base = 10;
    string decimal_string = "";                                 // stores the result
    bool is_negative = (num < 0);
    
    if (is_negative) {
        num = 0 - num;                                          // get the absolute value of the input number
    }
    
    while (num / base > 0) {                                    // recursively divide the input number by the base
        string remainder = to_string(num % base);               // get the remainder
        decimal_string = remainder + decimal_string;            // push each remainder to the first digit of the result
        num /= base;
    }
    
    decimal_string = to_string(num) + decimal_string;           // push the last remainder to the first digit of the result
    
    if (is_negative) {
        decimal_string = "-" + decimal_string;                  // fetch our dash mark to negate the result
    }
    
    return decimal_string;
}

string intToBinaryString(int num) {
    int base = 2;                                               // same as intToDecimalString() except for the base
    string binary_string = "";
    bool is_negative = (num < 0);
    
    if (is_negative) {
        num = 0 - num;
    }
    
    while (num / base > 0) {
        string remainder = to_string(num % base);
        binary_string = remainder + binary_string;
        num /= base;
    }
    
    binary_string = to_string(num) + binary_string;
    
    if (is_negative) {
        binary_string = "-" + binary_string;
    }
    
    return binary_string;
}

string intToHexadecimalString(int num) {
    int base = 16;
    string hexadecimal_string = "";
    bool is_negative = (num < 0);
    
    if (is_negative) {
        num = 0 - num;
    }
    
    while (num / base > 0) {
        int remainder = num % base;
        char char_remainder = hexitDigitConverter(remainder);   // call the function to convert ints between 10 and 15 into A to F
        hexadecimal_string = char_remainder + hexadecimal_string;
        num /= base;
    }
    
    hexadecimal_string = hexitDigitConverter(num) + hexadecimal_string; // same here
    
    if (is_negative) {
        hexadecimal_string = "-" + hexadecimal_string;
    }
    
    return hexadecimal_string;
}

char hexitDigitConverter(int digit) {                           // convert ints who are between 10 and 15 into A to F
    char char_digit = '0' + digit;
    
    if (digit > 9 && digit < 16)                                // if the int is between 10 and 15
        char_digit = 'A' + digit - 10;                          // do ASCII value calculation
    
    return char_digit;
}
