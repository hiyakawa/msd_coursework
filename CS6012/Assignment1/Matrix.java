/*
 * Matrix.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 1: Matrix
 * File 1 of 2
 */

package assignment01;

public class Matrix {
    int numRows_;
    int numColumns_;
    int data_[][];

    // constructor with data for new matrix (automatically determines dimensions)
    public Matrix(int data[][]) {
        // d.length is the number of 1D arrays in the 2D array
        numRows_ = data.length;

        if (numRows_ == 0) {
            numColumns_ = 0;
        }
        else {
            numColumns_ = data[0].length;
            // d[0] is the first 1D array
        }

        // create a new matrix to hold the data
        data_ = new int[numRows_][numColumns_];

        // copy the data over
        for (int curRow = 0; curRow < numRows_; curRow++) {
            for (int curCol = 0; curCol < numColumns_; curCol++) {
                data_[curRow][curCol] = data[curRow][curCol];
            }
        }
    }

    // copy constructor
    public Matrix(Matrix matrix) {
        numRows_ = matrix.numRows_;
        numColumns_ = matrix.numColumns_;
        data_ = new int[numRows_][numColumns_];

        // copy the data over
        for (int curRow = 0; curRow < numRows_; curRow++) {
            for (int curCol = 0; curCol < numColumns_; curCol++) {
                data_[curRow][curCol] = matrix.data_[curRow][curCol];
            }
        }
    }

    // constructor for an empty matrix
    public Matrix(int numRows, int numCols) {
        if (numRows <= 0 || numCols <= 0) {
            numRows_ = 0;
            numColumns_ = 0;
        }
        else {
            numRows_ = numRows;
            numColumns_ = numCols;
            data_ = new int[numRows_][numColumns_];
        }
    }

    @Override
    public boolean equals(Object other) {
        // make sure the Object we're comparing to is a Matrix
        if (!(other instanceof Matrix)) {
            return false;
        }

        // if the above was not true, we know it's safe to treat 'o' as a Matrix
        Matrix rhsMatrix = (Matrix) other;

        // not equal if the dimensions are different
        if (numColumns_ != rhsMatrix.numColumns_
                || numRows_ != rhsMatrix.numRows_) {
            return false;
        }

        // compare each element
        for (int curRow = 0; curRow < numRows_; curRow++) {
            for (int curCol = 0; curCol < numColumns_; curCol++) {
                if (data_[curRow][curCol] != rhsMatrix.data_[curRow][curCol]) {
                    return false;
                }
            }
        }

        return true;
    }

    @Override
    public String toString() {
        String matrixStr = "";

        if (numRows_ == 0) {
            return "Oops! You are trying to print an empty matrix..";
        }

        for (int curRow = 0; curRow < numRows_; curRow++) {
            for (int curCol = 0; curCol < numColumns_; curCol++) {
                // adding spaces after each element
                matrixStr += (data_[curRow][curCol] + " ");
            }
            // adding new line after each row
            matrixStr += "\n";
        }

        return matrixStr;
    }

    // addition
    public Matrix plus(Matrix rhsMatrix) {
        // check if the dimensions of the two matrices are compatible
        if (numColumns_ != rhsMatrix.numColumns_
                || numRows_ != rhsMatrix.numRows_
                || numRows_ == 0) {
            System.out.println("not compatible [error message from plus(Matrix)]");
            return null;
        }

        Matrix result = new Matrix(numRows_, numColumns_);

        for (int i = 0; i < numRows_; i++) {
            for (int j = 0; j < numColumns_; j++) {
                result.data_[i][j] = data_[i][j] + rhsMatrix.data_[i][j];
            }
        }

        return result;
    }

    // matrix multiplication
    public Matrix times(Matrix rhsMatrix) {
        // check if the dimensions of the two matrices are compatible
        if (numColumns_ != rhsMatrix.numRows_
                || numRows_ == 0 || rhsMatrix.numRows_ == 0) {
            System.out.println("not compatible [error message from times(Matrix)]");
            return null;
        }

        Matrix result = new Matrix(numRows_, rhsMatrix.numColumns_);

        // iterate through the two matrices
        for (int curRow = 0; curRow < numRows_; curRow++) {
            for (int curCol = 0; curCol < rhsMatrix.numColumns_; curCol++) {
                int curElementValue = 0;

                // calculate the elements in the result matrix
                for (int curElement = 0; curElement < numColumns_; curElement++) {
                    curElementValue += data_[curRow][curElement] * rhsMatrix.data_[curElement][curCol];
                }

                // push the current element to the result matrix
                result.data_[curRow][curCol] = curElementValue;
            }
        }

        return result;
    }

    // scalar multiplication
    public Matrix times(int scale) {
        Matrix result = new Matrix(this);

        for (int i = 0; i < result.numRows_; i++) {
            for (int j = 0; j < result.numColumns_; j++) {
                // avoid integer overflow
                long curElement = (long) result.data_[i][j] * scale;

                if (curElement > Integer.MAX_VALUE) {
                    System.out.println("integer overflow [error message from times(int)]");
                    return null;
                }

                result.data_[i][j] *= scale;
            }
        }

        return result;
    }

    // transposition
    public Matrix transpose() {
        Matrix result = new Matrix(numColumns_, numRows_);

        // copy the data over
        for (int curRow = 0; curRow < numRows_; curRow++) {
            for (int curCol = 0; curCol < numColumns_; curCol++) {
                result.data_[curCol][curRow] = data_[curRow][curCol];
            }
        }

        return result;
    }
}
