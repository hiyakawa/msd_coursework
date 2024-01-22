//
//  BookAnalyzer.h
//  BookAnalyzer
//
//  Created by Laura Zhang on 9/1/22.
//

#ifndef BookAnalyzer_h
#define BookAnalyzer_h

#include <string>
#include <vector>

enum ParseResult {
    Success = 0,
    WrongFileName = -1,
    OpenFailed = -2,
    NoKeyWord = -3,
    NoInputFile = -4,
    TooManyArguments = -5,
};

int parseFile(const char* file_name, std::string lookup_word);

int error_message(const char* file_name, std::string err_message, int err_type);

#endif /* BookAnalyzer_h */
