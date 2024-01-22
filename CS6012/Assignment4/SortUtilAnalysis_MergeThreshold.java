package assignment04;

import java.util.*;

public class SortUtilAnalysis_MergeThreshold {
    private static final int ITER_COUNT = 100;

    public static void main(String[] args) {
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

                if (k != thresholds.length -1) {
                    sb.append("\t");
                }
            }
            String s = sb.toString();
            System.out.println((s + "\n"));
            size *= 2;
        }
    }
}
