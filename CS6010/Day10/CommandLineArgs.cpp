//
//  main.cpp
//  CommandLineArgs
//
//  Created by Laura Zhang on 9/2/22.
//
//  Q: What is the first element of the argv array (argv[0])?
//  A: The relative path of the current project.

#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
// Alternatively:
// int main(int argc, const char** argv) {
    for (int i = 1; i < argc; i++) {
        cout << argv[i] << endl;
    }
    
    return 0;
}
