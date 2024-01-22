//
//  main.cpp
//  RoadTripCalculator
//
//  Created by Laura Zhang on 8/23/22.
//

#include <iostream>

using namespace std;

int main() {
    int driving_distance = -1;                                                      // miles
    cout << "Please enter the driving distance, in (whole) miles: " << endl;
    cin >> driving_distance;
    
    float miles_per_gallon = -1;
    cout << "Please enter the vehicle's miles per gallon efficiency: " << endl;
    cin >> miles_per_gallon;
    
    float dollar_per_gallon = -1;
    cout << "Please enter the cost of gas in dollars per gallon: " << endl;
    cin >> dollar_per_gallon;
    
    float number_of_gallons = driving_distance / miles_per_gallon;
    cout << "The number of gallons you used is " << number_of_gallons << "gallons." << endl;
    
    float cost_of_trip = number_of_gallons * dollar_per_gallon;
    cout << "The cost of the trip is " << cost_of_trip << "dollars." << endl;
    
    return 0;
}
