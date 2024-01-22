/*
 * SortUtilTest.java
 * Author: Muyuan Zhang
 * Partner: Gloria Dukuzeyesu
 * CS 6012 Assignment 4: Quicksort and Mergesort
 * File 2 of 2
 */

package assignment04;

import assignment02.Book;
import assignment02.LibraryBookGeneric;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Random;
import static assignment04.SortUtil.*;
import static org.junit.Assert.assertTrue;
import static org.junit.jupiter.api.Assertions.*;

class SortUtilTest {
    int ITER_COUNT = 100;
    ArrayList<Integer> ascIntList, avgIntList, descIntList;
    ArrayList<String> randomStrList;
    ArrayList<LibraryBookGeneric<String>> randomBookList, ascBookList, descBookList;

    LibraryBookGeneric<String> book1, book2, book3;

    Comparator<Integer> defaultIntComparator, reversedIntComparator;
    Comparator<String> defaultStrComparator, reversedStrComparator;
    Comparator<Book> defaultIsbnComparator, reversedIsbnComparator;

    @BeforeEach
    public void setUp() {
        ascIntList = generateBestCase(100);
        avgIntList = generateAverageCase(100);
        descIntList = generateWorstCase(100);
        randomStrList = new ArrayList<>();

        for (int i = 0; i < 100; i++) {
            Random rand = new Random();
            String randStr = "";
            int randInt = rand.nextInt(10) + 1;

            for (int j = 0; j < randInt; j++) {
                randStr += (char) (rand.nextInt(26) + 'a');
                randStr += (char) (rand.nextInt(26) + 'A');
            }

            randomStrList.add(randStr);
        }

        book1 = new LibraryBookGeneric<>
                (9780374292799L, "Thomas L. Friedman", "The World is Flat");
        book2 = new LibraryBookGeneric<>
                (9780446580342L, "David Baldacci", "Simple Genius");
        book3 = new LibraryBookGeneric<>
                (9780330351690L, "Jon Krakauer", "Into the Wild");

        randomBookList = new ArrayList<>() {{
            add(book1); add(book2); add(book3);}};

        ascBookList = new ArrayList<>() {{
            add(book3); add(book1); add(book2);}};

        descBookList = new ArrayList<>() {{
            add(book2); add(book1); add(book3);}};

        defaultIntComparator = Integer::compare;
        reversedIntComparator = (o1, o2)
                -> ((Comparable<Integer>) o2).compareTo(o1);

        defaultStrComparator = CharSequence::compare;
        reversedStrComparator = (o1, o2)
                -> ((Comparable<String>) o2).compareTo(o1);

        defaultIsbnComparator = (o1, o2)
                -> ((Comparable<Long>) o1.getIsbn()).compareTo(o2.getIsbn());
        reversedIsbnComparator = (o1, o2)
                -> ((Comparable<Long>) o2.getIsbn()).compareTo(o1.getIsbn());
    }

    @Test
    public void thresholdTimer() {
        int[] thresholds = {1, 20, 30, 40, 50};
        long startTime = System.nanoTime();
        while (System.nanoTime() - startTime < 1_000_000_000);

        int size = (int) Math.pow(2, 10);

        for (int i = 0; i < 11; i++) {
            long[] totalTime = new long[thresholds.length];
            Arrays.fill(totalTime, 0);

            for (int iter = 0; iter < ITER_COUNT; iter++) {
                ArrayList<Integer> initial = SortUtil.generateAverageCase(size);

                for (int k = 0; k < thresholds.length; k++) {
                    SortUtil.setThreshold(thresholds[k]);
                    ArrayList<Integer> temp = new ArrayList<>(initial);
                    long start = System.nanoTime();
                    SortUtil.mergesort(temp, Integer::compareTo);
                    long stop = System.nanoTime();
                    totalTime[k] += stop - start;
                }
            }

            double[] averageTime = new double[thresholds.length];
            StringBuilder sb = new StringBuilder();
            sb.append(size).append("\t");

            for (int k = 0; k < thresholds.length; k++) {
                averageTime[k] = totalTime[k] / (double) ITER_COUNT;
                sb.append(averageTime[k]);

                if (k != thresholds.length - 1) {
                    sb.append("\t");
                }
            }

            String s = sb.toString();
            System.out.println((s + "\n"));
            size *= 2;
        }
    }

    @Test
    public void pivotTimer() {
        PivotStrategy[] pivotStrategies = {
                PivotStrategy.FIRST, PivotStrategy.MEDIAN_OF_THREE, PivotStrategy.LAST};
        long startTime = System.nanoTime();
        while (System.nanoTime() - startTime < 1_000_000_000);

        int size = (int) Math.pow(2, 10);

        for (int i = 0; i < 11; i++) {
            long[] totalTime = new long[pivotStrategies.length];
            Arrays.fill(totalTime, 0);

            for (int iter = 0; iter < ITER_COUNT; iter++) {
                ArrayList<Integer> initial = SortUtil.generateAverageCase(size);

                for (int k = 0; k < pivotStrategies.length; k++) {
                    SortUtil.setPivot(pivotStrategies[k]);
                    ArrayList<Integer> temp = new ArrayList<>(initial);
                    long start = System.nanoTime();
                    SortUtil.mergesort(temp, Integer::compareTo);
                    long stop = System.nanoTime();
                    totalTime[k] += stop - start;
                }
            }

            double[] averageTime = new double[pivotStrategies.length];
            StringBuilder sb = new StringBuilder();
            sb.append(size).append("\t");

            for (int k = 0; k < pivotStrategies.length; k++) {
                averageTime[k] = totalTime[k] / (double) ITER_COUNT;
                sb.append(averageTime[k]);

                if (k != pivotStrategies.length - 1) {
                    sb.append("\t");
                }
            }

            String s = sb.toString();
            System.out.println((s + "\n"));
            size *= 2;
        }
    }

    @Test
    public void bestAlgorithm() {
        long startTime = System.nanoTime();
        while (System.nanoTime() - startTime < 1_000_000_000);
        setThreshold(30);
        setPivot(PivotStrategy.MEDIAN_OF_THREE);

        int size = (int) Math.pow(2, 10);

        for (int i = 0; i < 11; i++) {
            ArrayList<Integer> list = SortUtil.generateAverageCase(size);
            long totalTime = 0;

            for (int iter = 0; iter < ITER_COUNT; iter++) {
                ArrayList<Integer> temp = new ArrayList<>(list);
                long start = System.nanoTime();
                SortUtil.mergesort(temp, Integer::compareTo);
//                SortUtil.quicksort(temp, Integer::compareTo);
                long stop = System.nanoTime();
                totalTime += stop - start;
            }

            long averageTime = totalTime / ITER_COUNT;
            System.out.println(size + "\t" + averageTime);
            size *= 2;
        }
    }

    @Test
    public void mergesortTest() {
        assertThrows(NullPointerException.class, () ->
                mergesort(ascIntList, null));

        assertThrows(NullPointerException.class, () ->
                mergesort(null, defaultIntComparator));

        mergesort(ascIntList, reversedIntComparator);
        assertTrue(isNonAscendingSorted(ascIntList));

        mergesort(avgIntList, reversedIntComparator);
        assertTrue(isNonAscendingSorted(avgIntList));

        mergesort(descIntList, defaultIntComparator);
        assertTrue(isNonDescendingSorted(descIntList));

        // random string list
        mergesort(randomStrList, reversedStrComparator);
        assertTrue(isNonAscendingSorted(randomStrList));
    }

    @Test
    public void quicksortTest() {
        assertThrows(NullPointerException.class, () ->
                quicksort(ascIntList, null));

        assertThrows(NullPointerException.class, () ->
                quicksort(null, defaultIntComparator));

        quicksort(ascIntList, reversedIntComparator);
        assertTrue(isNonAscendingSorted(ascIntList));

        quicksort(avgIntList, reversedIntComparator);
        assertTrue(isNonAscendingSorted(avgIntList));

        quicksort(descIntList, defaultIntComparator);
        assertTrue(isNonDescendingSorted(descIntList));

        // random string list
        quicksort(randomStrList, reversedStrComparator);
        assertTrue(isNonAscendingSorted(randomStrList));
    }

    @Test
    public void bookSortingTest(){
        mergesort(randomBookList, defaultIsbnComparator);
        assertEquals(randomBookList, ascBookList);

        mergesort(randomBookList, reversedIsbnComparator);
        assertEquals(randomBookList, descBookList);

        quicksort(randomBookList, defaultIsbnComparator);
        assertEquals(randomBookList, ascBookList);

        quicksort(randomBookList, reversedIsbnComparator);
        assertEquals(randomBookList, descBookList);
    }

    @Test
    public void generateBestCaseTest() {
        assertNull(generateBestCase(-10));
        assertNull(generateBestCase(0));

        ArrayList<Integer> bestCaseArrayList = generateBestCase(100);
        SortUtil.printArrayList(bestCaseArrayList);
    }

    @Test
    public void generateAverageCaseTest() {
        assertNull(generateAverageCase(-10));
        assertNull(generateAverageCase(0));

        ArrayList<Integer> averageArrayList = generateAverageCase(100);
        SortUtil.printArrayList(averageArrayList);
    }

    @Test
    public void generateWorstCaseTest() {
        assertNull(generateWorstCase(-10));
        assertNull(generateWorstCase(0));

        ArrayList<Integer> worstArrayList = generateWorstCase(100);
        SortUtil.printArrayList(worstArrayList);
    }
}