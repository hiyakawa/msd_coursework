//
//  main.cpp
//  BookAnalyzer
//
//  Created by Laura Zhang on 9/1/22.
//

#include "BookAnalyzer.h"

#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
    string err_message = "";
    
    // if only 1 argument is passed, which is the program
    if (argc == 1) {
        err_message = "No input file is given!";
        return error_message("", err_message, NoInputFile);
    }
    
    const char* file_name = argv[1];
    
    // if only 2 argument is passed, which are the program and the input file name
    if (argc == 2) {
        err_message = "No key word is given!";
        return error_message(file_name, err_message, NoKeyWord);
    }
    
    // if the number of arguments is correct
    if (argc == 3) {
        string key_word = argv[2];
        
        // ./BookAnalyzer mobydick.txt weltering
        // ./BookAnalyzer test.txt fox
        
        switch (parseFile(file_name, key_word)) {
            case WrongFileName:
                err_message = "This file does not exist!";
                return error_message(file_name, err_message, WrongFileName);
                
            case OpenFailed:
                err_message = "File open failed!";
                return error_message(file_name, err_message, OpenFailed);
                
            case Success:
                return Success;
        }
    }
    
    // if the number of arguments is larger than 3
    err_message = "Too many arguments entered!";
    return error_message("", err_message, TooManyArguments);
}
