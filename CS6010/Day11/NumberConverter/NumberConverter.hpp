//
//  NumberConverter.hpp
//  NumberConverter
//
//  Created by Laura Zhang on 9/6/22.
//  Group members: Muyuan Zhang, Levi Neely, Lydia Yuan, Lauryn C.
//

#ifndef NumberConverter_hpp
#define NumberConverter_hpp

#include <string>

enum error_code {
    invalid_input = -1,
};

int stringToInt(const std::string num, int base);

bool isNumeric(char c);

bool isValidLetter(char c);

std::string intToDecimalString(int num);

std::string intToBinaryString(int num);

std::string intToHexadecimalString(int num);

char hexitDigitConverter(int digit);

#endif /* NumberConverter_hpp */
