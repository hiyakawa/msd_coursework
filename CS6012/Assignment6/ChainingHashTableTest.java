/*
 * ChainingHashTableTest.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 6: Hash Tables
 * File 2 of 6
 */

package assignment06;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Random;

import static java.lang.Math.abs;
import static org.junit.Assert.*;

class ChainingHashTableTest {
    GoodHashFunctor goodHashFunctor = new GoodHashFunctor();
    MediocreHashFunctor mediocreHashFunctor = new MediocreHashFunctor();
    BadHashFunctor badHashFunctor = new BadHashFunctor();
    ChainingHashTable goodFunctorHashTable,
            mediocreFunctorHashTable, badFunctorHashTable;
    ArrayList<String> listWithNull, strList;
    private static final int ITER_COUNT = 10;

    @BeforeEach
    void setUp() {
        int capacity = 16;
        goodFunctorHashTable = new ChainingHashTable(capacity, goodHashFunctor);
        mediocreFunctorHashTable = new ChainingHashTable(capacity, mediocreHashFunctor);
        badFunctorHashTable = new ChainingHashTable(capacity, badHashFunctor);

        strList = new ArrayList<>() {{add("I"); add("testing"); add("function.");}};
        listWithNull = new ArrayList<>() {{add("list"); add("with"); add(null);}};
    }

    @Test
    void countCollisions() {
        int size = 10000;

        for (int i = 1; i < 21; i++) {
            countCollisionsHelper(i * 1000, size);
        }
    }

    private void countCollisionsHelper(int capacity, int size) {
        int goodFunctorCollisions = 0;
        int mediocreFunctorCollisions = 0;
        int badFunctorCollisions = 0;
        ArrayList<Integer> goodFunctorIndices = new ArrayList<>(capacity);
        ArrayList<Integer> mediocreFunctorIndices = new ArrayList<>(capacity);
        ArrayList<Integer> badFunctorIndices = new ArrayList<>(capacity);

        for (int i = 0; i < size; i++) {
            Random rand = new Random();
            String randStr = "";
            int randInt = rand.nextInt(10) + 1;

            for (int j = 0; j < randInt; j++) {
                randStr += (char) (rand.nextInt(26) + 'a');
            }

            int goodIndex = abs(goodHashFunctor.hash(randStr) % capacity);
            if (goodFunctorIndices.contains(goodIndex)) {
                goodFunctorCollisions++;
            }
            else {
                goodFunctorIndices.add(goodIndex);
            }

            int mediocreIndex = abs(mediocreHashFunctor.hash(randStr) % capacity);
            if (mediocreFunctorIndices.contains(mediocreIndex)) {
                mediocreFunctorCollisions++;
            }
            else {
                mediocreFunctorIndices.add(mediocreIndex);
            }

            int badIndex = abs(badHashFunctor.hash(randStr) % capacity);
            if (badFunctorIndices.contains(badIndex)) {
                badFunctorCollisions++;
            }
            else {
                badFunctorIndices.add(badIndex);
            }
        }

        System.out.println("size: " + size + " capacity: " + capacity);
        System.out.println(goodFunctorCollisions + " " +
                mediocreFunctorCollisions + " " + badFunctorCollisions);
    }

    @Test
    public void countRunningTime() {
        HashFunctor[] funcs = {badHashFunctor, mediocreHashFunctor, goodHashFunctor};

        long startTime = System.nanoTime();
        while (System.nanoTime() - startTime < 1_000_000_000);

        System.out.println("size\tbad\tmediocre\tgood");
        int size = (int) Math.pow(2, 10);
        for (int i = 0; i < 11; i++) {
            ChainingHashTable[] tables = new ChainingHashTable[3];

            for (int j = 0; j < funcs.length; j++) {
                tables[j] = new ChainingHashTable(size, funcs[j]);
            }
            while(tables[0].size() < size) {
                Random rand = new Random();
                String randStr = "";
                int randInt = rand.nextInt(10) + 1;

                for (int j = 0; j < randInt; j++) {
                    randStr += (char) (rand.nextInt(26) + 'a');
                }

                for (int j = 0; j < funcs.length; j++) {
                    tables[j].add(randStr);
                }
            }
            int[] totalTime = new int[funcs.length];
            for (int iter = 0; iter < ITER_COUNT; iter++) {
                Random rand = new Random();
                String randStr = "";
                int randInt = rand.nextInt(10) + 1;

                for (int j = 0; j < randInt; j++) {
                    randStr += (char) (rand.nextInt(26) + 'a');
                }

                for (int j = 0; j < funcs.length; j++) {
                    tables[j].add(randStr);
                }

                for (int j = 0; j < funcs.length; j++) {
                    long start = System.nanoTime();
                    tables[j].remove(randStr);
                    long stop = System.nanoTime();
                    totalTime[j] += stop - start;
                    tables[j].remove(randStr);
                }
            }
            double[] averageTime = new double[funcs.length];
            StringBuilder sb = new StringBuilder();
            sb.append(size);
            for (int k = 0; k < funcs.length; k++) {
                averageTime[k] = totalTime[k] / (double) ITER_COUNT;
                sb.append("\t").append(averageTime[k]);
            }
            String s = sb.toString();
            System.out.println(s);
            size *= 2;
        }
    }

    @Test
    void add() {
        badFunctorHashTable.add("I");
        badFunctorHashTable.add("am");
        badFunctorHashTable.add("testing");
        badFunctorHashTable.add("add()");
        badFunctorHashTable.add("function.");

        badFunctorHashTable.printTable();
    }

    @Test
    void addAll() {
        badFunctorHashTable.addAll(strList);

        badFunctorHashTable.printTable();
    }

    @Test
    void clear() {
        badFunctorHashTable.add("I");
        badFunctorHashTable.add("am");
        badFunctorHashTable.add("testing");
        badFunctorHashTable.add("clear()");
        badFunctorHashTable.add("function.");

        badFunctorHashTable.clear();
        assertTrue(badFunctorHashTable.isEmpty());
    }

    @Test
    void contains() {
        try {
            goodFunctorHashTable.contains(null);
        }
        catch (NullPointerException e) {}

        goodFunctorHashTable.add("I");
        goodFunctorHashTable.add("am");
        goodFunctorHashTable.add("testing");
        goodFunctorHashTable.add("contains()");
        goodFunctorHashTable.add("function.");

        assertTrue(goodFunctorHashTable.contains("I"));
        assertTrue(goodFunctorHashTable.contains("testing"));
        assertTrue(goodFunctorHashTable.contains("function."));
        assertFalse(goodFunctorHashTable.contains("hello"));
    }

    @Test
    void containsAll() {
        try {
            goodFunctorHashTable.containsAll(null);
        }
        catch (NullPointerException e) {}

        try {
            goodFunctorHashTable.containsAll(listWithNull);
        }
        catch (NullPointerException e) {}

        goodFunctorHashTable.add("I");
        goodFunctorHashTable.add("am");
        goodFunctorHashTable.add("testing");
        goodFunctorHashTable.add("containsAll()");
        goodFunctorHashTable.add("function.");

        assertTrue(goodFunctorHashTable.containsAll(strList));

        strList.add("hello");
        assertFalse(goodFunctorHashTable.containsAll(strList));
    }

    @Test
    void isEmpty() {
        assertTrue(goodFunctorHashTable.isEmpty());

        goodFunctorHashTable.add("I");
        goodFunctorHashTable.add("am");
        goodFunctorHashTable.add("testing");
        goodFunctorHashTable.add("isEmpty()");
        goodFunctorHashTable.add("function.");
        assertFalse(goodFunctorHashTable.isEmpty());
    }

    @Test
    void remove() {
        try {
            goodFunctorHashTable.remove(null);
        }
        catch (NullPointerException e) {}

        goodFunctorHashTable.add("I");
        goodFunctorHashTable.add("am");
        goodFunctorHashTable.add("testing");
        goodFunctorHashTable.add("remove()");
        goodFunctorHashTable.add("function.");

        assertTrue(goodFunctorHashTable.remove("testing"));
        assertFalse(goodFunctorHashTable.remove("testing"));
        assertFalse(goodFunctorHashTable.remove("hello"));
    }

    @Test
    void removeAll() {
        try {
            goodFunctorHashTable.removeAll(null);
        }
        catch (NullPointerException e) {}

        try {
            goodFunctorHashTable.removeAll(listWithNull);
        }
        catch (NullPointerException e) {}

        goodFunctorHashTable.add("I");
        goodFunctorHashTable.add("am");
        goodFunctorHashTable.add("testing");
        goodFunctorHashTable.add("removeAll()");
        goodFunctorHashTable.add("function.");

        assertTrue(goodFunctorHashTable.removeAll(strList));
        assertFalse(goodFunctorHashTable.removeAll(strList));

        strList.add("hello");
        assertFalse(goodFunctorHashTable.removeAll(strList));
    }

    @Test
    void size() {
        assertEquals(0, goodFunctorHashTable.size());

        goodFunctorHashTable.add("I");
        goodFunctorHashTable.add("am");
        goodFunctorHashTable.add("testing");
        goodFunctorHashTable.add("size()");
        goodFunctorHashTable.add("function.");
        assertEquals(5, goodFunctorHashTable.size());
    }
}