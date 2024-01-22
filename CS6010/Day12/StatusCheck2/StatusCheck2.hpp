//
//  StatusCheck2.hpp
//  StatusCheck2
//
//  Created by Laura Zhang on 9/7/22.
//

#ifndef StatusCheck2_hpp
#define StatusCheck2_hpp

#include <string>

struct Dog {
    std::string name;
    int age;
    bool is_vaccinated;
};

int parseFile(const char* file_name);

bool isVowel(char c);

int countVowel(std::string& word);

#endif /* StatusCheck2_hpp */
