package assignment04;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.Random;

public class SortUtilAnalysis_QuickPivot {
    private static final int ITER_COUNT = 500;

    public static void main(String[] args) {
        long startTime;

        // First, spin computing stuff until one second has gone by.
        // This allows this thread to stabilize.
        startTime = System.nanoTime();
        while (System.nanoTime() - startTime < 1_000_000_000){ // empty block
        }

        // This is used as the exponent to calculate the size of the set.
        for (int exp = 10; exp <= 18; exp++) {
            int size = (int) Math.pow(2, exp);

            // Do the experiment multiple times, and average out the results
            long totalTime = 0;

            // SET UP!
            ArrayList<Integer> averageList = SortUtil.generateAverageCase(size);
            Comparator<Integer> comparator = Integer::compareTo;

            for (int iter = 0; iter < ITER_COUNT; iter++) {

                ArrayList<Integer> list = new ArrayList<>(averageList);

                // TIME IT!
                long start = System.nanoTime();
                SortUtil.quicksort(list, comparator);
                long stop = System.nanoTime();
                totalTime += stop - start;
            }

            double averageTime = (totalTime / (double) ITER_COUNT) / 100000 ;
            System.out.println(size + "\t" + averageTime);

        }

    }
}
