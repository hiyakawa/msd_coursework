# Templatized Vector

#### Muyuan Zhang

## Features

* implemented the methods of std::vector 
including constructor, copy constructor, destructor, 
`=`, `[]`, `==`, `!=`, `<`, `<=`, `>`, `>=`, 
`get()`, `set()`, `growVector()`, 
`push_back()`, `pop_back()`, 
`getSize()`, `getCapacity()`

* support for vector of `int`, `double`, `string` and `char`

## Output Example

```
===============================
    tests for MyVector<int>    
===============================

The elements in intVec1 are:
10 9 8 7 6 5 4 3 2 1 
intVec1's size is 10, capacity is 16

***** tests for copy constructor *****

The elements in intVec2 are:
10 9 8 7 6 5 4 3 2 1 
intVec2's size is 10, capacity is 16

***** tests for operator=() **********

The elements in intVec3 are:
10 9 8 7 6 5 4 3 2 1 
intVec3's size is 10, capacity is 16

***** tests for operator[]() *********

The 9th element in intVec2 is modified.

The elements in intVec2 are:
10 9 8 7 6 5 4 3 2 10 
intVec2's size is 10, capacity is 16

***** tests for operator==() *********
intVec1 == intVec2? 0
intVec1 == intVec3? 1

***** tests for operator!=() *********
intVec1 != intVec2? 1
intVec1 != intVec3? 0

***** tests for operator<() **********
intVec1 <  intVec2? 1
intVec1 <  intVec3? 0

***** tests for operator<=() *********
intVec1 <= intVec2? 1
intVec2 <= intVec3? 0

***** tests for operator>() **********
intVec1 >  intVec2? 0
intVec2 >  intVec3? 1

***** tests for operator>=() *********
intVec1 >= intVec2? 0
intVec2 >= intVec3? 1

===============================
   tests for MyVector<double>  
===============================

The elements in dblVec1 are:
10.1 9.1 8.1 7.1 6.1 5.1 4.1 3.1 2.1 1.1 0.1 
dblVec1's size is 11, capacity is 16

***** tests for copy constructor *****

The elements in dblVec2 are:
10.1 9.1 8.1 7.1 6.1 5.1 4.1 3.1 2.1 1.1 0.1 
dblVec2's size is 11, capacity is 16

***** tests for operator=() **********

The elements in dblVec3 are:
10.1 9.1 8.1 7.1 6.1 5.1 4.1 3.1 2.1 1.1 0.1 
dblVec3's size is 11, capacity is 16

***** tests for operator[]() *********

The 10th element in dblVec2 is modified.

The elements in dblVec2 are:
10.1 9.1 8.1 7.1 6.1 5.1 4.1 3.1 2.1 1.1 10.1 
dblVec2's size is 11, capacity is 16

***** tests for operator==() *********
dblVec1 == dblVec2? 0
dblVec1 == dblVec3? 1

***** tests for operator!=() *********
dblVec1 != dblVec2? 1
dblVec1 != dblVec3? 0

***** tests for operator<() **********
dblVec1 <  dblVec2? 1
dblVec1 <  dblVec3? 0

***** tests for operator<=() *********
dblVec1 <= dblVec2? 1
dblVec2 <= dblVec3? 0

***** tests for operator>() **********
dblVec1 >  dblVec2? 0
dblVec2 >  dblVec3? 1

***** tests for operator>=() *********
dblVec1 >= dblVec2? 0
dblVec2 >= dblVec3? 1

===============================
   tests for MyVector<string>  
===============================

The elements in strVec1 are:
abc d ef 
strVec1's size is 3, capacity is 4

***** tests for copy constructor *****

The elements in strVec2 are:
abc d ef 
strVec2's size is 3, capacity is 4

***** tests for operator=() **********

The elements in strVec3 are:
abc d ef 
strVec3's size is 3, capacity is 4

***** tests for operator[]() *********

The 2th element in strVec2 is modified.

The elements in strVec2 are:
abc d abc 
strVec2's size is 3, capacity is 4

***** tests for operator==() *********
strVec1 == strVec2? 0
strVec1 == strVec3? 1

***** tests for operator!=() *********
strVec1 != strVec2? 1
strVec1 != strVec3? 0

***** tests for operator<() **********
strVec1 <  strVec2? 0
strVec1 <  strVec3? 0

***** tests for operator<=() *********
strVec1 <= strVec2? 0
strVec2 <= strVec3? 1

***** tests for operator>() **********
strVec1 >  strVec2? 1
strVec2 >  strVec3? 0

***** tests for operator>=() *********
strVec1 >= strVec2? 1
strVec2 >= strVec3? 0

===============================
   tests for MyVector<char>    
===============================

The elements in charVec1 are:
c a e q 1 
charVec1's size is 5, capacity is 8

***** tests for copy constructor *****

The elements in charVec2 are:
c a e q 1 
charVec2's size is 5, capacity is 8

***** tests for operator=() **********

The elements in charVec3 are: 
c a e q 1 
charVec3's size is 5, capacity is 8

***** tests for operator[]() *********

The 4th element in charVec2 is modified.

The elements in charVec2 are:
c a e q c 
charVec2's size is 5, capacity is 8

***** tests for operator==() *********
charVec1 == charVec2? 0
charVec1 == charVec3? 1

***** tests for operator!=() *********
charVec1 != charVec2? 1
charVec1 != charVec3? 0

***** tests for operator<() **********
charVec1 <  charVec2? 1
charVec1 <  charVec3? 0

***** tests for operator<=() *********
charVec1 <= charVec2? 1
charVec2 <= charVec3? 0

***** tests for operator>() **********
charVec1 >  charVec2? 0
charVec2 >  charVec3? 1

***** tests for operator>=() *********
charVec1 >= charVec2? 0
charVec2 >= charVec3? 1
```
