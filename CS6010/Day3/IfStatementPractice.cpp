//
//  main.cpp
//  IfStatementPractice
//
//  Created by Laura Zhang on 8/24/22.
//

#include <iostream>
#include <string>

using namespace std;

int main() {
    // Part 1
    int users_age = -1;
    cout << "Enter your age:" << endl;
    cin >> users_age;
    
    // keep prompting the user for their age if they enter negative numbers or zero
    while (users_age < 1 || users_age > 150) {
        cout << "Your age should be a positive integer between 1 and 150. Enter your age again:" << endl;
        cin >> users_age;
    }
    
    // check if the user is able to vote
    bool is_able_to_vote = false;
    
    if (users_age > 17) {
        is_able_to_vote = true;
    }
    
    // check if the user is able to run for senate
    bool is_able_to_senate = false;
    
    if (users_age > 29) {
        is_able_to_senate = true;
    }
    
    // check which generation the user belongs to
    string generation = "";
    
    if (users_age > 80) {
        generation = "greatest generation";
    }
    
    else if (users_age > 60) {
        generation = "baby boomers";
    }
    
    else if (users_age > 40) {
        generation = "generation X";
    }
    
    else if (users_age > 20) {
        generation = "millennial";
    }
    
    else {
        generation = "iKid";
    }
    
    // print the results
    if (is_able_to_vote) {
        cout << "Congrats! You are able to vote." << endl;
    }
    
    else {
        cout << "Sorry, you can only vote if you are over 18 years old." << endl;
    }
    
    if (is_able_to_senate) {
        cout << "Congrats! You are able to run for senate." << endl;
    }
    
    else {
        cout << "Sorry, you can only run for senate if you are over 30 years old." << endl;
    }
    
    cout << "Your generation is " << generation << "!" << endl;
    
    // Part 2
    
    // prompt the user to enter whether or not it's a weekday
    bool is_weekday;
    char weekday_response;
    cout << "Enter whether or not it's a weekday (Y/N):" << endl;
    cin >> weekday_response;
    
    while (weekday_response != 'Y' && weekday_response != 'N') {
        cout << "Your answer should be either Y (for yes) or N (for no). ";
        cout << "Enter whether or not it's a weekday (Y/N):" << endl;
        cin >> weekday_response;
    }
    
    if (weekday_response == 'Y') {
        is_weekday = true;
    }
    
    if (weekday_response == 'N') {
        is_weekday = false;
    }
    
    // prompt the user to enter whether or not it's a holiday
    bool is_holiday;
    char holiday_response;
    cout << "Enter whether or not it's a holiday (Y/N):" << endl;
    cin >> holiday_response;
    
    while (holiday_response != 'Y' && holiday_response != 'N') {
        cout << "Your answer should be either Y (for yes) or N (for no). ";
        cout << "Enter whether or not it's a holiday (Y/N):" << endl;
        cin >> holiday_response;
    }
    
    if (holiday_response == 'Y') {
        is_holiday = true;
    }
    
    if (holiday_response == 'N') {
        is_holiday = false;
    }
    
    // prompt the user to enter whether or not they have young children
    bool has_children;
    char children_response;
    cout << "Enter whether or not you have young children (Y/N):" << endl;
    cin >> children_response;
    
    while (children_response != 'Y' && children_response != 'N') {
        cout << "Your answer should be either Y (for yes) or N (for no). ";
        cout << "Enter whether or not you have young children (Y/N):" << endl;
        cin >> children_response;
    }
    
    if (children_response == 'Y') {
        has_children = true;
    }
    
    if (children_response == 'N') {
        has_children = false;
    }
    
    // check if the user can get to sleep
    bool is_able_to_sleep;
    
    if (! has_children) {
        if (! is_weekday || is_holiday) {
            is_able_to_sleep = true;
        }
    }
    
    else {
        is_able_to_sleep = false;
    }
    
    // print the results
    if (is_able_to_sleep) {
        cout << "Congrats! You are able to get to sleep today." << endl;
    }
    
    else {
        cout << "Sorry! You are not able to get to sleep today." << endl;
    }
    
    return 0;
}
