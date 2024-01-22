//
//  WordHelpers.hpp
//  StringAnalyzer
//
//  Created by Laura Zhang on 8/29/22.
//

#ifndef WordHelpers_hpp
#define WordHelpers_hpp

#include <stdio.h>

int NumWords(std::string s);

int NumSentences(std::string s);

int NumVowels(std::string s);

int NumConsonants(std::string s);

double AverageWordLength(std::string s);

double AverageVowelsPerWord(std::string s);

#endif /* WordHelpers_hpp */
