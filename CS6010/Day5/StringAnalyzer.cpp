//
//  main.cpp
//  stringAnalyzer
//
//  Created by Laura Zhang on 8/26/22.
//

#include <iostream>
#include <string>

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

int main() {
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
