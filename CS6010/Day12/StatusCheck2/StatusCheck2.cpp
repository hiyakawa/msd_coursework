//
//  StatusCheck2.cpp
//  StatusCheck2
//
//  Created by Laura Zhang on 9/7/22.
//

#include "StatusCheck2.hpp"

#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int parseFile(const char* file_name) {
    ifstream myStream(file_name);
    
    if (! filesystem::exists(file_name)) {        // if the file does not exist
        exit(-1);                                 // return -1
    }
    
    if (myStream.fail()) {                        // if we fail to open the file
        exit(-2);                                 // return -2
    }

    string word = "";
    vector<string> words;
    
    while (myStream >> word) {                    // read the file and extract words
            words.push_back(word);                // push each non-empty string into the vector
    }
    
    myStream.close();
    
    int total_vowel = 0;
    
    for (string each_word : words) {
        total_vowel += countVowel(each_word);
    }
    
    return total_vowel;
}
    
// takes in a character and returns whether that character is a vowel
bool isVowel(char c) {
    c = tolower(c);
    
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
        return true;
    }
    
    return false;
}

// takes in a word and returns the number of vowels in that word
int countVowel(string& word) {
    int vowel_counter = 0;
    
    for (char c : word) {
        if (isVowel(c)) {
            vowel_counter++;
        }
    }
    
    return vowel_counter;
}
