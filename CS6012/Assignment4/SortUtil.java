/*
 * SortUtil.java
 * Author: Muyuan Zhang
 * Partner: Gloria Dukuzeyesu
 * CS 6012 Assignment 4: Quicksort and Mergesort
 * File 1 of 2
 */

package assignment04;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.Random;

public class SortUtil<T> {
    public enum PivotStrategy {
        FIRST,
        LAST,
        MEDIAN_OF_THREE
    }
    private static PivotStrategy curStrategy_ = PivotStrategy.LAST;
    private static int threshold_ = 30;

    /**
     * @param arrayList the array list to be sorted.
     * @param comparator throws an exception if the input comparator is null.
     * @param <T> type of the elements in the array list.
     */
    public static <T> void mergesort(ArrayList<T> arrayList,
                                     Comparator<? super T> comparator) {
        checkNull(arrayList, comparator);

        // create a temperate array list
        ArrayList<T> tempArrayList = new ArrayList<>(arrayList.size());
//        T placeholderElement = arrayList.get(0);

        // fill in it with the size of the original array list
        for (int i = 0; i < arrayList.size(); i++) {
            tempArrayList.add(null);
//            tempArrayList.add(placeholderElement);
        }

        mergesort(arrayList, tempArrayList, comparator, 0, arrayList.size());
    }

    /**
     * @param arrayList the array list to be sorted.
     * @param tempArrayList sorted subarray.
     * @param comparator throws an exception if the input comparator is null.
     * @param start the starting index of the subarray.
     * @param end the last index of the subarray.
     * @param <T> type of the elements in the array list.
     */
    private static <T> void mergesort(ArrayList<T> arrayList,
                                      ArrayList<T> tempArrayList,
                                      Comparator<? super T> comparator,
                                      int start, int end) {
        // jump out of the method if current sub array has only 0 or 1 element
        if (end - start < 2) {
            return;
        }

        // switch to insertion sort if current sub array size hits threshold
        if (end - start <= threshold_) {
            insertionSort(arrayList, comparator, start, end);
        }
        else {
            int mid = (start + end) / 2;

            // recursion
            mergesort(arrayList, tempArrayList, comparator, start, mid);
            mergesort(arrayList, tempArrayList, comparator, mid, end);
            merge(arrayList, tempArrayList, comparator, start, mid, end);
        }
    }

    /**
     * @param arrayList the array list to be sorted.
     * @param tempArrayList sorted subarray.
     * @param comparator throws an exception if the input comparator is null.
     * @param start the starting index of the subarray.
     * @param mid the middle index of the subarray.
     * @param end the last index of the subarray.
     * @param <T> type of the elements in the array list.
     */
    private static <T> void merge(ArrayList<T> arrayList,
                                          ArrayList<T> tempArrayList,
                                          Comparator<? super T> comparator,
                                          int start, int mid, int end) {
        int left = start, right = mid, ptr = start;

        for (; left < mid && right < end; ptr++) {
            if (comparator.compare(arrayList.get(left),
                    arrayList.get(right)) <= 0) {
                tempArrayList.set(ptr, arrayList.get(left++));
            }
            else {
                tempArrayList.set(ptr, arrayList.get(right++));
            }
        }

        for (; left < mid; left++) {
            tempArrayList.set(ptr++, arrayList.get(left));
        }

        for (; right < end; right++) {
            tempArrayList.set(ptr++, arrayList.get(right));
        }

        // copy the sorted array to the original one
        for (int i = start; i < end; i++) {
            arrayList.set(i, tempArrayList.get(i));
        }
    }

    /**
     * @param arrayList the array list to be sorted.
     * @param comparator the comparator passed from mergesort().
     * @param <T> type of the elements in the array list.
     */
    private static <T> void insertionSort(ArrayList<T> arrayList,
                                          Comparator<? super T> comparator,
                                          int start, int end) {
        for (int i = start + 1; i < end; i++) {
            for (int j = i; j > start &&
                 comparator.compare(arrayList.get(j),
                                    arrayList.get(j - 1)) < 0; j--) {
                swap(arrayList, j - 1, j);
            }
        }
    }

    /**
     * @param threshold input threshold.
     */
    public static void setThreshold(int threshold) {
        threshold_ = threshold;
    }

    /**
     * @param arrayList the array list to be sorted.
     * @param comparator throws an exception if the input comparator is null.
     * @param <T> type of the elements in the array list.
     */
    public static <T> void quicksort(ArrayList<T> arrayList,
                                     Comparator<? super T> comparator) {
        checkNull(arrayList, comparator);
        quicksort(arrayList, comparator, 0, arrayList.size() - 1);
    }

    /**
     * @param arrayList the array list to be sorted.
     * @param comparator throws an exception if the input comparator is null.
     * @param start lower index.
     * @param end higher index.
     * @param <T> type of the elements in the array list.
     */
    private static <T> void quicksort(ArrayList<T> arrayList,
                                      Comparator<? super T> comparator,
                                      int start, int end) {
        if (start < end) {
            int partitionIndex = partition(arrayList, comparator, start, end);

            quicksort(arrayList, comparator, start, partitionIndex - 1);
            quicksort(arrayList, comparator, partitionIndex + 1, end);
        }
    }

    /**
     * @param arrayList the array list to be sorted.
     * @param comparator throws an exception if the input comparator is null.
     * @param start lower index.
     * @param end higher index.
     * @param <T> type of the elements in the array list.
     * @return the index of pivot.
     */
    private static <T> int partition(ArrayList<T> arrayList,
                          Comparator<? super T> comparator,
                          int start, int end) {
        int pivotIndex;
        // implement three different strategies for determining the pivot
        switch (curStrategy_) {
            case FIRST -> pivotIndex = start;
            case LAST -> pivotIndex = end;
            case MEDIAN_OF_THREE -> pivotIndex = (start + end) / 2;
            default -> throw new UnsupportedOperationException("Illegal pivot.");
        }

        T pivot = arrayList.get(pivotIndex);
        int leftIndex = start - 1;

        for (int rightIndex = start; rightIndex < end; rightIndex++) {
            if (comparator.compare(arrayList.get(rightIndex), pivot) <= 0) {
                leftIndex++;
                swap(arrayList, leftIndex, rightIndex);
            }
        }

        swap(arrayList, leftIndex + 1, end);
        return leftIndex + 1;
    }

    /**
     * @param curStrategy pass the input PivotStrategy to curStrategy_.
     */
    public static void setPivot(PivotStrategy curStrategy) {
        curStrategy_ = curStrategy;
    }

    /**
     * @param arrayList the array list to be sorted.
     * @param lhsIndex the index of the left hand side element to be swapped.
     * @param rhsIndex the index of the right hand side element to be swapped.
     * @param <T> type of the elements in the array list.
     */
    private static <T> void swap(ArrayList<T> arrayList,
                                 int lhsIndex, int rhsIndex) {
        // skip swapping if the indexes are the same
        if (lhsIndex != rhsIndex) {
            T temp = arrayList.get(lhsIndex);
            arrayList.set(lhsIndex, arrayList.get(rhsIndex));
            arrayList.set(rhsIndex, temp);
        }
    }

    /**
     * @return an ArrayList of integers 1 to size in ascending order.
     */
    public static ArrayList<Integer> generateBestCase(int size) {
        if (size < 1) {
            throw new IllegalArgumentException("The size should be grater than 0.");
        }

        ArrayList<Integer> ascendingIntArr = new ArrayList<>();

        for (int i = 1; i <= size; i++) {
            ascendingIntArr.add(i);
        }

        return ascendingIntArr;
    }

    /**
     * @return an ArrayList of integers 1 to size in permuted order.
     */
    public static ArrayList<Integer> generateAverageCase(int size) {
        if (size < 1) {
            throw new IllegalArgumentException("The size should be grater than 0.");
        }

        ArrayList<Integer> randIntArr = new ArrayList<>();
        Random rand = new Random();

        for (int i = 0; i < size; i++) {
            int randInt = rand.nextInt(size - 1) + 1;
            randIntArr.add(randInt);
        }

        return randIntArr;
    }

    /**
     * @return an ArrayList of integers 1 to size in descending order.
     */
    public static ArrayList<Integer> generateWorstCase(int size) {
        if (size < 1) {
            throw new IllegalArgumentException("The size should be grater than 0.");
        }

        ArrayList<Integer> descendingIntArr = new ArrayList<>();

        for (int i = size; i > 0; i--) {
            descendingIntArr.add(i);
        }

        return descendingIntArr;
    }

    /**
     * Helper method to throw null exceptions.
     * @param arrayList the array list to be checked.
     * @param comparator the comparator to be checked.
     * @param <T> type of the elements in the array list.
     */
    private static <T> void checkNull(ArrayList<T> arrayList,
                                      Comparator<? super T> comparator) {
        if (arrayList == null) {
            throw new NullPointerException("Array List is null.");
        }

        if (comparator == null) {
            throw new NullPointerException("Comparator is null.");
        }
    }

    /**
     * @param arrayList the array list to be printed.
     */
    public static <T> void printArrayList(ArrayList<T> arrayList) {
        try {
            for (int i = 0; i < arrayList.size(); i++) {
                System.out.print(arrayList.get(i) + " ");

                if (i % 10 == 9) {
                    System.out.println("");
                }
            }
            System.out.println("");
        }
        catch (Exception e) {
            System.out.println("not able to print the elements");
        }
    }

    /**
     * @param arrayList the array list to be checked.
     * @return whether the current array list is non-descending sorted or not.
     * @param <T> type of the elements in the array list.
     */
    public static <T> boolean isNonDescendingSorted(ArrayList<T> arrayList) {
        try {
            // get the default comparator of type T
            Comparator<T> comparator = (o1, o2) ->
                    ((Comparable<T>) o1).compareTo(o2);

            // compare each element with the next element
            for (int i = 0; i < arrayList.size() - 1; i++) {
                if (comparator.compare(arrayList.get(i), arrayList.get(i + 1)) > 0) {
                    return false;
                }
            }
            return true;
        }
        catch (Exception e) {
            e.printStackTrace();
            throw new UnsupportedOperationException();
        }
    }

    /**
     * @param arrayList the array list to be checked.
     * @return whether the current array list is non-ascending sorted or not.
     * @param <T> type of the elements in the array list.
     */
    public static <T> boolean isNonAscendingSorted(ArrayList<T> arrayList) {
        try {
            // get the default comparator of type T
            Comparator<T> comparator = (o1, o2) ->
                    ((Comparable<T>) o1).compareTo(o2);

            // compare each element with the next element
            for (int i = 0; i < arrayList.size() - 1; i++) {
                if (comparator.compare(arrayList.get(i), arrayList.get(i + 1)) < 0) {
                    return false;
                }
            }

            return true;
        }
        catch (Exception e) {
            e.printStackTrace();
            throw new UnsupportedOperationException();
        }
    }
}
