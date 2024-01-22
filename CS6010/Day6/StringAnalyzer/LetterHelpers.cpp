//
//  LetterHelpers.cpp
//  StringAnalyzer
//
//  Created by Laura Zhang on 8/29/22.
//

#include "LetterHelpers.hpp"

using namespace std;

// Returns whether or not the character is ., ?, or !.
bool IsTerminator(char c) {
    if (c == '.' || c == '?' || c == '!') {
        return true;
    }
    
    return false;
}

// Returns whether or not the character is ., ?, !, or ,.
bool IsPunctuation(char c) {
    if (c == '.' || c == '?' || c == '!' || c == ',') {
        return true;
    }
    
    return false;
}

// Returns whether or not the character is a vowel.
// treat the character 'y' (and its uppercase version) as a vowel.
bool IsVowel(char c) {
    // convert the char to a lowercase letter
    c = tolower(c);
    
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y') {
        return true;
    }
    
    return false;
}

// Returns whether or not the character is a consonant.
bool IsConsonant(char c) {
    if (IsPunctuation(c) || IsVowel(c) || c == ' ') {
        return false;
    }
    
    return true;
}
