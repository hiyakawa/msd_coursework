#include <iostream>

using namespace std;

struct MyVector {
    double* data;
    int size;
    int capacity;
};

double arrayModSum(MyVector& someVar) {
    double array_sum = 0;

    // adding 1 to each element
    for (int i = 0; i < someVar.size; i++) {
        someVar.data[i]++;
        array_sum += someVar.data[i];
    }

    // return the sum of the modified array
    return array_sum;
}

void growMyVector(MyVector& someVar) {
    int var_size = someVar.size;

    // allocate memory for a temporary array twice the size
    if (var_size == someVar.capacity) {
        double* temp_array = new double [var_size * 2];

        // copy the contents from someVar.data to this temp array
        for (int i = 0; i < var_size; i++) {
            temp_array[i] = someVar.data[i];
        }

        // double the size and the capacity
        someVar.size *= 2;
        someVar.capacity = someVar.size;

        // call delete[] on someVar.data to free up the old chunk of memory
        delete [] someVar.data;

        // set someVar.data = the pointer to the temp array
        someVar.data = & temp_array[0];

        // set the pointer to the temp array to nullptr
        temp_array = nullptr;
    }
}

int main(int argc, const char * argv[]) {
    MyVector vec1;

    int vec1_size = 0;
    cout << "Enter the size of the array:" << endl;
    cin >> vec1_size;

    vec1.data = new double [vec1_size];
    vec1.size = vec1_size;
    vec1.capacity = vec1_size;

    // fill each element with 1.0
    for(int i = 0; i < vec1_size; i++) {
        vec1.data[i] = 1.0;
    }

    // print out the returned sum of the modified array
    cout << "The sum of the modified array is ";
    cout << arrayModSum(vec1) << endl;

    growMyVector(vec1);

    cout << "After growing the vector, the size is " << vec1.size;
    cout << ", and capacity is " << vec1.capacity << endl;

    delete [] vec1.data;
    vec1.data = nullptr;

    return 0;
}
