//
//  main.cpp
//  PoliStructs
//
//  Created by Laura Zhang on 8/30/22.
//

#include "PoliStructs.h"
#include <iostream>

using namespace std;

// Takes a vector of politicians and returns a vector with
// only the politicians from the input that are Javacans.
vector<Politician> Javacans(vector<Politician> all_politicians) {
    string javacans = "Javacans";
    vector<Politician> javacans_politicians;
    
    for (Politician cur_politician : all_politicians) {
        if (cur_politician.party == javacans) {
            javacans_politicians.push_back(cur_politician);
        }
    }
    
    return javacans_politicians;
}

// Takes a vector of politicians as a parameter and returns
// a list of the federal Cplusers from the input.
list<string> federalCplusers(vector<Politician> all_politicians) {
    string cplusers = "Cplusers";
    string federal = "federal";
    list<string> federal_cplusers;
    
    for (Politician cur_politician : all_politicians) {
        if (cur_politician.party == cplusers &&
            cur_politician.state_or_federal == federal) {
            federal_cplusers.push_back(cur_politician.name);
        }
    }
    
    return federal_cplusers;
}

// Print every element in a Politician vector
void politicianVectorPrinter(vector<Politician> all_politicians) {
    for (Politician cur_politician : all_politicians) {
        cout << cur_politician.name << ", " << cur_politician.party << ", " << cur_politician.state_or_federal << endl;
    }
}

// Print every element in a string list
void stringListPrinter(list<string> all_politicians) {
    for (string cur_politician : all_politicians) {
        cout << cur_politician << endl;
    }
}

// Error message
void errorExit(string message) {
    cerr << "Failed test: " << message << endl;
    exit(1);
}

int main(int argc, const char * argv[]) {
    Politician ava {"Ava", "Javacans", "state"};
    Politician elijah {"Elijah", "Javacans", "federal"};
    Politician layla {"Layla", "Cplusers", "state"};
    Politician oliver {"Oliver", "Cplusers", "federal"};
    Politician stella {"Stella", "Javacans", "state"};
    Politician sebastian {"Sebastian", "Javacans", "federal"};
    Politician evelyn {"Evelyn", "Cplusers", "state"};
    Politician anthony {"Anthony", "Cplusers", "federal"};
    
    vector<Politician> all_politicians = {ava, elijah, layla, oliver, stella, sebastian, evelyn, anthony};
    vector<Politician> javacans_politicians = {ava, elijah, stella, sebastian};
    list<string> federal_cplusers = {"Oliver", "Anthony"};
    
    // print all the politicians
    cout << "All politicians:" << endl;
    politicianVectorPrinter(all_politicians);
    cout << endl;
    
    // print Javacans politicians
    cout << "Javacans politicians:" << endl;
    politicianVectorPrinter(Javacans(all_politicians));
    cout << endl;
    
    // print federal and Cplusers politicians
    cout << "Federal and Cplusers politicians:" << endl;
    stringListPrinter(federalCplusers(all_politicians));
    cout << endl;
    
    // unit tests
    if (federalCplusers(all_politicians) != federal_cplusers) {
        errorExit( "federalCplusers() - test 2" );
    };
    
    cout << "All tests passed!" << endl;
    
    return 0;
}
