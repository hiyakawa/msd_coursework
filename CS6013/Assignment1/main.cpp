//
//  main.cpp
//  Assembly Programming
//
//  Created by Laura Zhang on 1/26/23.
//

extern "C" {
    // declaration only
    void sayHello();
    int myPuts(const char* s, int len);
}

int main(int argc, const char * argv[]) {
    // part 1 - sayHello()
    sayHello();
    
    // part 2 - making a system call
    myPuts("hi!\n", 5);
    myPuts("testing myPuts()\n", 18);
    myPuts("end of testing\n", 16);
    
    return 0;
}
