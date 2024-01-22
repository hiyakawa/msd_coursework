//
//  main.cpp
//  StringAnalyzer
//
//  Created by Laura Zhang on 8/29/22.
//

#include <iostream>
#include "WordHelpers.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // prompt the user to enter sentences
    cout << "Enter a string containing one or more sentences:" << endl;
    string input;
    getline(cin, input);
    
    // repeatedly asks the user for input strings
    while (input != "done") {
        cout << "Analysis:" << endl;
        
        // call the functions and print the results
        int num_words = NumWords(input);
        cout << " Number of words: " << num_words << endl;
        
        int num_sentences = NumSentences(input);
        cout << " Number of sentences: " << num_sentences << endl;
        
        int num_vowels = NumVowels(input);
        cout << " Number of vowels: " << num_vowels << endl;
        
        int num_consonants = NumConsonants(input);
        cout << " Number of consonants: " << num_consonants << endl;
        
        double average_word_length = AverageWordLength(input);
        cout << " Reading level (average word length): " << average_word_length << endl;
        
        double average_vowels_per_word = AverageVowelsPerWord(input);
        cout << " Average vowels per word: " << average_vowels_per_word << endl;
        
        cout << endl << "Enter a string containing one or more sentences:" << endl;
        getline(cin, input);
    }
    
    // ends when the user types "done"
    cout << "Goodbye." << endl;
    
    return 0;
}
