//
//  main.cpp
//  statuscheck
//
//  Created by Laura Zhang on 8/29/22.
//

#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    cout << "Enter 4 numbers from 1 to 10, or -99 to quit:" << endl;
    int input;
    int sum_input = 0;
    int valid_inputs = 0;
    cin >> input;
    
    while (valid_inputs < 4 && input != -99) {
        if (input < 1 || input > 10) {
            cout << "Your number must between 1 and 10, or -99 to quit:" << endl;
            cin >> input;
        }
        
        else {
            sum_input += input;
            valid_inputs++;
            
            if (valid_inputs < 4) {
                cout << "Enter 4 numbers from 1 to 10, or -99 to quit:" << endl;
                cin >> input;
            }
        }
    }
    
    if (input == -99) {
        cout << "Goodbye." << endl;
    }
    
    cout << "The sum of numbers you entered is " << sum_input << endl;
    
    return 0;
}
