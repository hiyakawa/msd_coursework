/*
 * MatrixJUnitTester.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 1: Matrix
 * File 2 of 2
 */

package assignment01;

import org.junit.Assert;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class MatrixTest {
    Matrix oneByTen;
    Matrix tenByOne;
    Matrix twoByThree;
    Matrix threeByTwo;
    Matrix twoByTwo;
    Matrix twoByTwoCopy;

    @BeforeEach
    public void setUp() throws Exception {
        int[][] oneByTenData = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
        int[][] tenByOneData = {{-9}, {-8}, {-7}, {-6}, {-5}, {-4}, {-3}, {-2}, {-1}, {0}};
        int[][] twoByThreeData = {{1, -2, 3}, {-4, 5, 6}};
        int[][] threeByTwoData = {{7, 8}, {9, -10}, {11, 12}};
        int[][] twoByTwoData = {{22, 64}, {83, -10}};
        oneByTen = new Matrix(oneByTenData);
        tenByOne = new Matrix(tenByOneData);
        twoByThree = new Matrix(twoByThreeData);
        threeByTwo = new Matrix(threeByTwoData);
        twoByTwo = new Matrix(twoByTwoData);
        twoByTwoCopy = new Matrix(twoByTwoData);
    }

    @Test
    // testing equals(Matrix)
    public void equalsToItself() {
        // testing with the same matrix
        Assert.assertTrue(oneByTen.equals(oneByTen));

        // testing with two matrices with the same data
        Assert.assertTrue(twoByTwo.equals(twoByTwoCopy));

        // testing with two matrices with different data
        Assert.assertFalse(twoByTwo.equals(twoByThree));
    }

    @Test
    // testing times(Matrix)
    public void timesWithBalancedDimensions() {
        // test two by three matrix times three by two matrix
        Matrix twoByThreeTimesThreeByTwo = twoByThree.times(threeByTwo);
        Assert.assertTrue(twoByTwo.equals(twoByThreeTimesThreeByTwo));

        // test two by two matrix times two by three matrix
        Matrix twoByTwoTimestwoByThree = twoByTwo.times(twoByThree);
        int[][] expectedTwoByTwoTimestwoByThreeData = {{-234, 276, 450}, {123, -216, 189}};
        Matrix expectedTwoByTwoTimestwoByThree = new Matrix(expectedTwoByTwoTimestwoByThreeData);
        Assert.assertTrue(expectedTwoByTwoTimestwoByThree.equals(twoByTwoTimestwoByThree));

        // test one by ten matrix times ten by one matrix
        Matrix oneByTenTimesTenByOne = oneByTen.times(tenByOne);
        int[][] expectedOneByTenTimesTenByOneData = {{-165}};
        Matrix expectedOneByTenTimesTenByOne = new Matrix(expectedOneByTenTimesTenByOneData);
        Assert.assertTrue(expectedOneByTenTimesTenByOne.equals(oneByTenTimesTenByOne));
    }

    @Test
    // testing times(Matrix)
    public void timesWithUnbalancedDimensions() {
        // should return null if the matrices are not compatible
        Matrix twoByThreeTimesTwoByTwo = twoByThree.times(twoByTwo);
        Assert.assertNull(twoByThreeTimesTwoByTwo);

        Matrix oneByTenTimesoneByTen = oneByTen.times(oneByTen);
        Assert.assertNull(oneByTenTimesoneByTen);
    }

    @Test
    // testing times(int)
    public void timesANumber() {
        // doing scalar multiplication involving negative integers
        Matrix twoByThreeTimesMinusTwo = twoByThree.times(-2);
        int[][] expectedtwoByThreeTimesMinusTwoData = {{-2, 4, -6}, {8, -10, -12}};
        Matrix expectedtwoByThreeTimesMinusTwo = new Matrix(expectedtwoByThreeTimesMinusTwoData);
        Assert.assertTrue(expectedtwoByThreeTimesMinusTwo.equals(twoByThreeTimesMinusTwo));
    }

    @Test
    // testing plus(Matrix)
    public void plusWithBalancedDimensions() {
        // test two by two matrix plus itself
        Matrix twoByTwoPlusTwoByTwo = twoByTwo.plus(twoByTwoCopy);
        int[][] expectedTwoByTwoPlusTwoByTwoData = {{44, 128}, {166, -20}};
        Matrix expectedTwoByTwoPlusTwoByTwo = new Matrix(expectedTwoByTwoPlusTwoByTwoData);
        Assert.assertTrue(twoByTwoPlusTwoByTwo.equals(expectedTwoByTwoPlusTwoByTwo));

        // test two by three matrix plus two by three matrix
        Matrix twoByThreePlusTwoByThree = twoByThree.plus(twoByThree);
        int[][] expectedTwoByThreePlusTwoByThreeData = {{2, -4, 6}, {-8, 10, 12}};
        Matrix expectedTwoByThreePlusTwoByThree = new Matrix(expectedTwoByThreePlusTwoByThreeData);
        Assert.assertTrue(twoByThreePlusTwoByThree.equals(expectedTwoByThreePlusTwoByThree));

        // test three by two matrix plus three by two matrix
        Matrix threeByTwoPlusThreeByTwo = threeByTwo.plus(threeByTwo);
        int[][] expectedThreeByTwoPlusThreeByTwoData = {{14, 16}, {18, -20}, {22, 24}};
        Matrix expectedThreeByTwoPlusThreeByTwo = new Matrix(expectedThreeByTwoPlusThreeByTwoData);
        Assert.assertTrue(threeByTwoPlusThreeByTwo.equals(expectedThreeByTwoPlusThreeByTwo));
    }

    @Test
    // testing plus(Matrix)
    public void plusWithUnbalancedDimensions() {
        // should return null if the matrices are not compatible
        Matrix oneByTenPlusThreeByTwo = oneByTen.plus(threeByTwo);
        Assert.assertNull(oneByTenPlusThreeByTwo);
    }

    @Test
    // testing toString(Matrix)
    public void twoByThreeToString() {
        String twoByThreeString = "1 -2 3 \n" +
                                  "-4 5 6 \n";
        Assert.assertEquals(twoByThreeString, twoByThree.toString());

        String tenByOneString = "-9 \n-8 \n-7 \n-6 \n-5 \n-4 \n-3 \n-2 \n-1 \n0 \n";
        Assert.assertEquals(tenByOneString, tenByOne.toString());
    }

    @Test
    // testing transpose(Matrix)
    public void twoByThreeTransposition() {
        int[][] threeByTwoResultData = {{1, -4}, {-2, 5}, {3, 6}};
        Matrix threeByTwoResult = new Matrix(threeByTwoResultData);
        Assert.assertTrue(threeByTwoResult.equals(twoByThree.transpose()));

        // transpose twice and get the original matrix
        Assert.assertTrue(twoByThree.equals(twoByThree.transpose().transpose()));
    }
}