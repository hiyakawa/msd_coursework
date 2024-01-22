#### 1. Where is the assertEquals method defined? What does it do? Can we use assertEquals for more than just int types? (Hint: Consult the API for JUnit)

A: It is defined in `public class Assert extends java.lang.Object`
 to assert two variables or objects are equal. 
 Yes, we can also use it for double/long/objects.



#### 2. Briefly describe what each of the three tests is checking.

A: Test 1 is to check if the return value of `findSmallestDiff()` 
of an empty array is -1.

Test 2 is to check if the return value is 0 if the elements in 
the array are all the same.

Test 3 is to check if the algorithm works for a small random array, 
especially when there are negative numbers in it.



#### 3. Why is our unimplemented findSmallestDiff method passing one of the tests?

A: Because the unimplemented findSmallestDiff() returns 0, and the expected return value of test 2 happens to be 0. 
They are equal and test 2 got an invalid answer.



#### 4. Why are we failing the third test? How should our method be modified to correct this?

A: There are negative numbers in test 3 and the method messed up the calculation without using absolute value. 
The method can be modified as:

```
public static int findSmallestDiff(int[] a) {
    if (a.length < 2) {
        return -1;
    }

    int diff = abs(a[0] - a[1]);                // abs here

    for (int i = 0; i < a.length; i++) {
        for (int j = i + 1; j < a.length; j++) {
            int tmp_diff = abs(a[i] - a[j]);    // abs here

            if (tmp_diff < diff) {
                diff = tmp_diff;
            }
        }
    }

    return diff;
}
```



#### 5. What is the appropriate call to assertEquals for your new test (test 4)?

A:
```
@Test
public void allDiffEqual() {
   assertEquals(2, DiffUtil.findSmallestDiff(arr4));
}
```



#### 6. Provide one more test (test 5) for the findSmallestDiff method. Briefly describe your test and write the call to assertEquals here.

A:
```
arr5 = new int[10000];
for (int i = 0; i < 10000; i++) {
    arr5[i] = i;
}
// generate a big array

@Test
public void bigArray() {
    assertEquals(1, DiffUtil.findSmallestDiff(arr5));
}
```



#### 7. Briefly describe your unit tests for Assignment 1.

A: Checked if the results are as expected when we call times() 
and plus() with matrices whose dimensions are compatible or 
not compatible with the calculation.
