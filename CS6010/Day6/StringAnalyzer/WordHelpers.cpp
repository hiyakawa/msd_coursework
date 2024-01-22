//
//  WordHelpers.cpp
//  StringAnalyzer
//
//  Created by Laura Zhang on 8/29/22.
//

#include "LetterHelpers.hpp"
#include "WordHelpers.hpp"

using namespace std;

// Returns the number of words in the string.
int NumWords(string s) {
    int space_counter = 0;
    
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            space_counter++;
        }
    }
    
    int num_words = space_counter + 1;
    return num_words;
}

// Returns the number of sentences in the string.
int NumSentences(string s) {
    int num_sentences = 0;
    
    for (int i = 0; i < s.length(); i++) {
        if (IsTerminator(s[i])) {
            num_sentences++;
        }
    }
    
    return num_sentences;
}

// Returns the number of vowels in the string.
int NumVowels(string s) {
    int num_vowels = 0;
    
    for (int i = 0; i < s.length(); i++) {
        if (IsVowel(s[i])) {
            num_vowels++;
        }
    }
    
    return num_vowels;
}

// Returns the number of consonants in the string.
int NumConsonants(string s) {
    int num_consonants = 0;
    
    for (int i = 0; i < s.length(); i++) {
        if (IsConsonant(s[i])) {
            num_consonants++;
        }
    }
    
    return num_consonants;
}

// Returns the average length of all words in the string.
double AverageWordLength(string s) {
    int num_letters = NumVowels(s) + NumConsonants(s);
    int num_words = NumWords(s);
    double average_word_length = 1.0 * num_letters / num_words;
    return average_word_length;
}

// Returns the average number of vowels per word in the string.
double AverageVowelsPerWord(string s) {
    int num_vowels = NumVowels(s);
    int num_words = NumWords(s);
    double average_vowels_per_word = 1.0 * num_vowels / num_words;
    return average_vowels_per_word;
}
