//
//  main.cpp
//  Average
//
//  Created by Reshma Raghavan on 8/23/22.
//  Group members: Laura Zhang, Reshma Raghavan
//  This is a program to calculate the average of a number of values
//  in this case, it is used to calculate the average of grades

#include <iostream>

using namespace std;

int main() {
    int assignmentScore1; int assignmentScore2; int assignmentScore3;
    int assignmentScore4; int assignmentScore5;
    
    cout << "Enter five assignment scores: " << endl;
    
    cin >> assignmentScore1 >> assignmentScore2 >> assignmentScore3 >> assignmentScore4 >> assignmentScore5;

    int totalScore = assignmentScore1 + assignmentScore2 + assignmentScore3 + assignmentScore4 + assignmentScore5;
    
    float scoreAverage = totalScore / 5.0;
    
    cout << "The average score of the five assignments is " << scoreAverage << endl;
    
    return 0;
}
