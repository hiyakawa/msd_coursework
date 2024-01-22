//
//  main.cpp
//  VectorPractice
//
//  Created by Laura Zhang on 8/29/22.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Takes a vector of ints as a parameter and returns the sum of
// all the values in the vector.
int sum(vector<int> numbers) {
    int element_sum = 0;
    
    for (int i : numbers) {
        element_sum += i;
    }
    
    return element_sum;
}

// Takes a string as a parameter and returns a vector of chars
// that contains the same data.
vector<char> stringToVec(string s) {
    vector<char> v;
    
    for (int i = 0; i < s.length(); i++) {
        v.push_back(s[i]);
    }
    
    return v;
}

// Takes a vector of ints and returns a vector with the same elements
// in reverse order.
vector<int> reverse(vector<int> v) {
    vector<int> reversed_v;
    
    for (int i = (v.size()-1); i >= 0; i--) {
        reversed_v.push_back(v[i]);
    }
    
    return reversed_v;
}

void ErrorExit( std::string message )
{
    cerr << "Failed test: " << message << endl;
    exit(1);
}

int main(int argc, const char * argv[]) {
    vector<int> v1 = {3, 1, 0, -1, 5};
    
    string s = "HelloWorld!";
    vector<char> v2 = {'H', 'e', 'l', 'l', 'o', 'W', 'o', 'r', 'l', 'd', '!'};
    
    vector<int> v3 = {5, -1, 0, 1, 3};
    
    if(sum(v1) != 8) {
        ErrorExit( "sum() - test 1" );
    }
    
    if(stringToVec(s) != v2) {
        ErrorExit( "stringToVec() - test 2" );
    }
    
    if(reverse(v1) != v3) {
        ErrorExit( "reverse() - test 3" );
    }
    
    cout << "All tests passed!" << endl;
    
    return 0;
}
