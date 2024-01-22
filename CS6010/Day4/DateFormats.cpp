//
//  main.cpp
//  DateFormats
//
//  Created by Laura Zhang on 8/25/22.
//  Group members: Laura Zhang, Levi Neely
//

#include <iostream>
#include <string>

using namespace std;

// a mini function to check if a year is a leap year
// reference: https://www.programiz.com/cpp-programming/examples/leap-year
bool isLeap(int year) {
    return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

int main() {
    // Part 2
    string inputDate = "";
    cout << "Enter a date:" << endl;
    cin >> inputDate;
    
    int index = 0;
    string month_str = "";
    string day_str = "";
    string year_str = "";
    
    // get the month
    while (index < inputDate.length() && inputDate[index] != '/' ) {
        month_str += inputDate[index];
        index++;
    }
    
    // move to the next char
    index++;
    
    // get the day
    while (index < inputDate.length() && inputDate[index] != '/' ) {
        day_str += inputDate[index];
        index++;
    }
    
    // move to the next char
    index++;
    
    // get the year
    while (index < inputDate.length() && inputDate[index] != '/' ) {
        year_str += inputDate[index];
        index++;
    }
    
    // convert strings to integers
    int month = stoi(month_str);
    int day = stoi(day_str);
    int year = stoi(year_str);
    
    // weeding out invalid inputs
    // reference: https://www.geeksforgeeks.org/program-check-date-valid-not
    int max_valid_day = 31;
    int min_valid_day = 1;
    int max_valid_month = 12;
    int min_valid_month = 1;
    int max_valid_year = 9999;
    int min_valid_year = 1000;
    
    string name_of_month = "";
    
    // check if month, day or year is in valid range
    // if it is a leap year, there should be no more than 29 days in Feburary
    // if it is not a leap year, no more than 28 days in Feburary
    // there should be no more than 30 days in April, June, September and November
    if (month < min_valid_month || month > max_valid_month ||
        day < min_valid_day || day > max_valid_day ||
        year < min_valid_year || year > max_valid_year ||
        (isLeap(year) && month == 2 && day > 29) ||
        ((!isLeap(year)) && month == 2 && day > 28) ||
        ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)) {
        cout << "Invalid date" << endl;
    }
    
    else {
        // replace months with the names of month
        if (month == 1) {
            name_of_month = "January";
        }
        if (month == 2) {
            name_of_month = "February";
        }
        if (month == 3) {
            name_of_month = "March";
        }
        if (month == 4) {
            name_of_month = "April";
        }
        if (month == 5) {
            name_of_month = "May";
        }
        if (month == 6) {
            name_of_month = "June";
        }
        if (month == 7) {
            name_of_month = "July";
        }
        if (month == 8) {
            name_of_month = "August";
        }
        if (month == 9) {
            name_of_month = "September";
        }
        if (month == 10) {
            name_of_month = "October";
        }
        if (month == 11) {
            name_of_month = "November";
        }
        if (month == 12) {
            name_of_month = "December";
        }
        
        // print out the final output
        cout << name_of_month << " " << day << ", " << year << endl;
    }
    
    return 0;
}
