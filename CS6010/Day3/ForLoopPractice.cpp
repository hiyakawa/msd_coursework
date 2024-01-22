//
//  main.cpp
//  ForLoopPractice
//
//  Created by Laura Zhang on 8/24/22.
//

#include <iostream>
using namespace std;

int main() {
    // for loop version to print 1 to 10
    cout << "Here are the numbers from 1 to 10 in a for loop version:" << endl;
    
    for (int i = 1; i < 11; i++) {
        cout << i << endl;
    }
    
    // while loop version to print 1 to 10
    cout << "Here are the numbers from 1 to 10 in a while loop version:" << endl;
    
    int j = 1;
    
    while (j < 11) {
        cout << j << endl;
        j++;
    }
    
    // absolutely prefer the for loop version!
    
    // prompt the user to enter the two numbers
    int former_num, latter_num;
    cout << "Enter two numbers, with the former smaller than the latter, splitted by enter:" << endl;
    cin >> former_num >> latter_num;
    
    // print error message if the numbers come in reverse order
    while (former_num >= latter_num) {
        cout << "The former number should be smaller than the latter!" << endl;
        cout << "Enter two numbers splitted by enter:" << endl;
        cin >> former_num >> latter_num;
    }
    
    // print the numbers from the first to the second
    cout << "Here are all the numbers from the first to the second:" << endl;
    
    for (int cur_num = former_num; cur_num <= latter_num; cur_num++) {
        cout << cur_num << endl;
    }
    
    // print all the odd numbers between 1 and 20
    // a loop and an if statement version
    cout << "Here are all the odd numbers from 1 to 20 with an if statement:" << endl;
    
    for (int i = 1; i < 21; i++) {
        if (i % 2 == 1) {
            cout << i << endl;
        }
    }
    
    // no if statement version
    cout << "Here are all the odd numbers from 1 to 20 without any if statements:" << endl;
    
    for (int i = 1; i < 21; i += 2) {
        cout << i << endl;
    }
    
    // prefer the version without if statement!
    
    // ask a user to enter positive numbers to add up
    int sum = 0;
    int cur_num = 0;
    
    do {
        cout << "Enter positive numbers splitted by enters. ";
        cout << "End up adding if you enter a negative number." << endl;
        cin >> cur_num;
        sum += cur_num;
    } while (cur_num >= 0);
    
    sum -= cur_num;
    
    cout << "The sum of numbers you entered is " << sum << endl;
    
    // print a multiplication table from 1 to 5
    for (int i = 1; i < 6; i++) {
        cout << i << "x*: ";
        
        for (int j = 1; j < 6; j++) {
            cout << i*j << " ";
        }
        cout << endl;
    }
    
    return 0;
}
