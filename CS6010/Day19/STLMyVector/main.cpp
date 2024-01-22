//
//  main.cpp
//  STLMyVector
//
//  Created by Laura Zhang on 9/20/22.
//

#include "STLMyVector.hpp"

#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;

int main(int argc, const char * argv[]) {
    MyVector<int> intVec1;
    
    for (int i = 10; i > 0; i--) {
        intVec1.pushBack(i);
    }
    
    cout << "The elements in intVec1 are:" << endl;
    
    std::for_each(intVec1.begin(), intVec1.end(), [] (const int& i) {cout << i << " ";});
    
    cout << endl << endl;

    std::sort(intVec1.begin(), intVec1.end());
    
    cout << "After sorted, the elements in intVec1 are:" << endl;
    
    std::for_each(intVec1.begin(), intVec1.end(), [] (const int& i) {cout << i << " ";});
    
    cout << endl << endl;
    
    int min_value = * std::min_element(intVec1.begin(), intVec1.end());
    cout << "The minimum element is " << min_value << endl << endl;
    
    int sum_value = std::accumulate(intVec1.begin(), intVec1.end(), 0);
    cout << "The sum of the vector is " << sum_value << endl << endl;
    
    // count even numbers in the vector
    // using a normal function
    int count_even = std::count_if(intVec1.begin(), intVec1.end(), isEvenNum);
    cout << "(normal function version) The number of even numbers is ";
    cout << count_even << endl << endl;
    
    // using a lambda function
    int count_even_lambda = std::count_if(intVec1.begin(), intVec1.end(), [](const int& i){return (i % 2 == 0);});
    cout << "(lambda function version) The number of even numbers is ";
    cout << count_even_lambda << endl << endl;
    
    // remove even numbers from the vector
    // using a normal function
    int count_even_num = std::count_if(intVec1.begin(), intVec1.end(), isEvenNum);
    
    std::remove_if(intVec1.begin(), intVec1.end(), isEvenNum);
    
//    for (unsigned int i = 0; i < count_even_num; i++) {
//        intVec1.popBack();
//    }
    
    cout << "After removing even numbers from the vector, the elements in intVec1 are:" << endl;
    std::for_each(intVec1.begin(), intVec1.end(), [] (const int& i) {cout << i << " ";});
    cout << endl << endl;
    
    // using a lambda function
    MyVector<int> intVec2;
    
    for (int i = 10; i > 0; i--) {
        intVec2.pushBack(i);
    }
    
    int count_even_num_lambda = std::count_if(intVec2.begin(), intVec2.end(), isEvenNum);
    
    std::remove_if(intVec2.begin(), intVec2.end(), [](const int& i){return (i % 2 == 0);});
    
    for (unsigned int i = 0; i < count_even_num_lambda; i++) {
        intVec2.popBack();
    }
    
    cout << "After removing even numbers from the vector, the elements in intVec2 are:" << endl;
    std::for_each(intVec2.begin(), intVec2.end(), [] (const int& i) {cout << i << " ";});
    cout << endl << endl;
    
    return 0;
}
