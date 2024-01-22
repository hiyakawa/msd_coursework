//
//  main.cpp
//  final
//
//  Created by Laura Zhang on 9/23/22.
//

#include "final.hpp"

#include <vector>
#include <iostream>

using namespace std;

void increaseGrades(std::vector<double> grades){
    for(int i=0; i < grades.size(); i++){
       grades[i] = grades[i] + 5;
       cout << grades[i] << endl;
    }

    for(int i=0; i < grades.size(); i++){
        cout << grades[i] << endl;
    }
}

int main() {
//    std::vector<double> grades = {1,2,3};
//    increaseGrades(grades);
//    for(int i=0; i < grades.size(); i++){
//        cout << grades[i] << endl;
//    }
    
//    MyString str1;
//    str1.pushBack('a');
//    str1.pushBack('b');
//
//    MyString str2;
//    str2.pushBack('c');
//    str2.pushBack('d');
//
//    MyString str3 = str1 + str2;
//
//    for (int i = 0; i < 4; i++) {
//        cout << str3.get(i) << endl;
//    }
    
    cout << templatizedPower('a', 2) << endl;
    cout << templatizedPower(1.1, 2) << endl;
    cout << templatizedPower(100.0, -1) << endl;
    
    return 0;
}
