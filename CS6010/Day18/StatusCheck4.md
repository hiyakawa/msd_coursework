# Status Check

Muyuan Zhang

#### a)

Computer memory is divided into two \* pieces, the heap and stack:

* What is the purpose of stack memory and how does it get allocated (grow) / deallocated?

* What is the purpose of heap memory and how is it allocated / deallocated?

* Why is there an \* next to the word two above?

Q:

* Stack memory stores temporary variables / parameters created by functions. Stack variables are automatically created / destroyed.

* Heap memory stores large chunks of data or global variables. Heap variables are not automatically created / destroyed.

* Uh, no idea. Doesn't mean `dereference` right?

#### b)

Naming of variables is a way to help understand the data that we are storing:

* For the variable pX, what does the p stand for and why is it there?

* For the variable data_, why is there an _ at the end of the name?

Q:

* `p` is for `pointer` as a more readable prefix.

* `_` means `data_` is a member variable of the class.

#### c)

Classes

* What is the difference between a class and an object? What is a good analogy for these things?

* What is the difference between a method and a function?

* Why do we use classes?

Q:

* An object is a variable that provides both data and functions on that data. Objects are instantiations of classes. Class is a blueprint from which objects are created.

* A function is a set of instructions or procedures to perform a specific task, and a method is a set of instructions that are associated with an object.

* For object-oriented programming to implement encapsulation, abstraction, inheritance, and polymorphism.

#### d)

Give the following code, draw a memory diagram (containing all variables (etc) and their values) showing the state after all code has executed. If a variables value changes, cross out the previous value and write the new value):

```
void doit( int x, int & y ) {
    x = 3;
    y = 4;
    MyVector * pV = new MyVector( 4 );
    pv->push_back( 99 );
}

int main() {
    int * x = new int[3];                   // new a pointer to an array of int on the heap with capacity of 3
    x[1] = 123;                             // set the 1st element as 123
    int a = 0;
    int b = 0;
    MyVector v( 4 );                        // Initial capacity of 4
    doit( a, b );                           // a == 3
                                            // b == 4
                                            // new a pointer to MyVector on the heap with capacity of 4
                                            // push 99 as a new element into that MyVector
}
```
