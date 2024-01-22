//
//  main.cpp
//  Palindromes
//
//  Created by Laura Zhang on 8/25/22.
//  Group members: Laura Zhang, Levi Neely
//

#include <iostream>
#include <string>

using namespace std;

int main() {
    // Part 1
    
    cout << "Enter a word:" << endl;
    string users_str = "";
    cin >> users_str;
    
    // get the length of the string
    int len_users_str = users_str.length();
    string reversed = "";
    
    // add chars into the reversed string
    for (int i = (len_users_str - 1); i >= 0; i--) {
        reversed += users_str[i];
    }
    
    // compare the original str with the reversed one
    if ((reversed.compare(users_str)) == 0) {
        cout << users_str << " IS a palindrome" << endl;
    }
    
    else {
        cout << users_str << " is NOT a palindrome" << endl;
    }
    
    return 0;
}
