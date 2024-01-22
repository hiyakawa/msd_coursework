//
//  main.cpp
//  FunctionPractice
//
//  Created by Laura Zhang on 8/26/22.
//

#include <iostream>
#include <string>
#include <cmath>
#include <ctime>

using namespace std;

// Part 2
// Write a function that performs the hypotenuse task.
double hypotenuseCalculator(double height_1, double height_2) {
    // calculate the length of hypotenuse
    double hypotenuse_len = sqrt(pow(height_1, 2) + pow(height_2, 2));
    
    // print the result
    cout << "This result comes from a function. ";
    cout << "The length of hypotenuse is " << hypotenuse_len << endl;
    
    // return the result
    return hypotenuse_len;
}


// Part 2
// Write a function isCapitalized that takes in a string parameter and
// returns whether or not the string starts with a capital letter.
bool isCapitalized(string str) {
    // check if the first char is in uppercase
    if (isupper(str[0])) {
        return true;
    }
    
    return false;
}

// Part 2
// Write a function boolToString that takes in a Boolean parameter
// and returns the string "true" or "false" depending on its value.
// Use this function to display the results of testing the isCapitalized function.
string boolToString(bool result) {
    string result_str = "false";
    
    // check if the bool is true
    if (result) {
        result_str = "true";
    }
    
    return result_str;
}

// Part 2
// Write a function called isPrime that takes an integer
// and returns whether or not it's a prime number.
bool isPrime(int number) {
    for (int i = 2; i < number; i++) {
        if (number % i == 0) {
            return false;
        }
    }
    
    return true;
}


int main() {
    // Part 1
    // a
    
    // prompt the user to input the lengths of a triangle
    cout << "Enter the right-angle side lengths of a triangle:" << endl;
    double height_1 = -1.0;
    double height_2 = -1.0;
    cin >> height_1 >> height_2;
    
    // refuse non-positive answers and print out error messages
    while (height_1 <= 0 || height_2 <= 0) {
        cout << "The lengths must be positive. ";
        cout << "Enter the right-angle side lengths of a triangle:" << endl;
        cin >> height_1 >> height_2;
    }
    
    // calculate the length of hypotenuse
    double hypotenuse_len = sqrt(pow(height_1, 2) + pow(height_2, 2));
    
    cout << "The length of hypotenuse is " << hypotenuse_len << endl;
    
    // Part 1
    // b
    
    // prompt the user to input the speed and the angle they're going
    cout << "Enter the speed and the angle you are going:" << endl;
    double speed = -1.0;
    double angle = -1.0;
    cin >> speed >> angle;
    
    // refuse non-positive answers and print out error messages
    while (speed <= 0 || angle <= 0) {
        cout << "The speed and angle must be positive. ";
        cout << "Enter the speed and the angle you are going:" << endl;
        cin >> speed >> angle;
    }
    
    // calculate the x and y velocity
    double x = speed * cos(angle);
    double y = speed * sin(angle);
    
    cout << "Your x velocity is " << x << endl;
    cout << "Your y velocity is " << y << endl;
    
    // Part 1
    // c
    
    std::time_t result = std::time(nullptr);
    std::cout << std::asctime(std::localtime(&result))
              << result << " seconds since the Epoch\n";
    
    /*
     Called functions:
        std::time()         // Returns the current time of the system as time since epoch
        std::cout           // Our old friend who prints things
        std::asctime()      // Converts given calendar time std::tm to a textual representation
                               of the following fixed 25-character form: Www Mmm dd hh:mm:ss yyyy\n
        std::localtime()    // Converts given time since epoch as std::time_t value into calendar time,
                               expressed in local time.
    */
    
    // Part 2
    // Write a function that performs the hypotenuse task.
    
    // prompt the user to input the lengths of a triangle
    cout << "Enter the right-angle side lengths of a triangle:" << endl;
    double height_1_part2 = -1.0;
    double height_2_part2 = -1.0;
    cin >> height_1_part2 >> height_2_part2;
    
    // refuse non-positive answers and print out error messages
    while (height_1_part2 <= 0 || height_2_part2 <= 0) {
        cout << "The lengths must be positive. ";
        cout << "Enter the right-angle side lengths of a triangle:" << endl;
        cin >> height_1_part2 >> height_2_part2;
    }
    
    // call the function
    double hyp_len = hypotenuseCalculator(height_1_part2, height_2_part2);
    
    // Part 2
    /*
     Q: Why would it be difficult to turn the speed/velocity task above into a function?
     A: Because it should return two variables which cannot be implemented by a double function.
        We can define a void function that only print the result and does not return anything.
    */
    
    // Part 2
    // Write a function isCapitalized that takes in a string parameter and
    // returns whether or not the string starts with a capital letter.
    
    // prompt the user to input a string
    cout << "Enter a string:"<< endl;
    string input_str = "";
    cin >> input_str;
    
    // call the function
    bool is_capitalized = isCapitalized(input_str);
    
    // Part 2
    // Write a function boolToString that takes in a Boolean parameter
    // and returns the string "true" or "false" depending on its value.
    // Use this function to display the results of testing the isCapitalized function.
    
    // call the function
    string is_capitalized_str = boolToString(is_capitalized);
    
    // pring the result of isCapitalized function
    cout << "Does your string starts with a capital letter?" << endl;
    cout << "The answer is " << is_capitalized_str << endl;
    
    // Part 2
    // Write a function called isPrime that takes an integer
    // and returns whether or not it's a prime number.
    
    // prompt the user to input a string
    cout << "Enter a positive integer greater than 1:"<< endl;
    int input_int = -1;
    cin >> input_int;
    
    // refuse non-positive answers and print out error messages
    while (input_int <= 1) {
        cout << "The number must be positive and greater than 1." << endl;
        cout << "Enter a positive integer greater than 1:" << endl;
        cin >> input_int;
    }
    
    // call the function
    bool is_prime = isPrime(input_int);
    
    // print the result
    if (is_prime) {
        cout << "The number you entered IS a prime number." << endl;
    }
    
    else {
        cout << "The number you entered is NOT a prime number." << endl;
    }
    
    return 0;
}
