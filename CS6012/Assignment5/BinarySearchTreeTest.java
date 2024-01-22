/*
 * BinarySearchTreeTest.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 5: Binary Search Trees
 * File 2 of 3
 */

package assignment05;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import java.util.ArrayList;
import java.util.NoSuchElementException;
import java.util.Random;
import static org.junit.Assert.*;
import static org.junit.Assert.assertFalse;

class BinarySearchTreeTest {
    BinarySearchTree<Integer> intBst = new BinarySearchTree<>();
    BinarySearchTree<Integer> intBstCopy = new BinarySearchTree<>();
    BinarySearchTree<Integer> emptyIntBst = new BinarySearchTree<>();
    BinarySearchTree<Integer> randomIntBst = new BinarySearchTree<>();
    BinarySearchTree<String> randomStrBst = new BinarySearchTree<>();

    ArrayList<Integer> intList = new ArrayList<>();
    ArrayList<Integer> intListWithNull = new ArrayList<>();

    @BeforeEach
    public void setUp() {
        intBst.add(2);
        intBst.add(6);
        intBst.add(1);
        intBst.add(3);
        intBst.add(5);
        intBst.add(7);

        intList = new ArrayList<>() {{
            add(2); add(6); add(1); add(3); add(5); add(7);}};
        intBstCopy.addAll(intList);

        intListWithNull = new ArrayList<>() {{
            add(2); add(6); add(1); add(3); add(5); add(null);}};

        for (int i = 0; i < 100; i++) {
            Random rand = new Random();
            int randInt = rand.nextInt(100);
            randomIntBst.add(randInt);
        }

        for (int i = 0; i < 100; i++) {
            Random rand = new Random();
            String randStr = "";
            int randInt = rand.nextInt(10) + 1;

            for (int j = 0; j < randInt; j++) {
                randStr += (char) (rand.nextInt(26) + 'a');
                randStr += (char) (rand.nextInt(26) + 'A');
            }

            randomStrBst.add(randStr);
        }
    }

    @Test
    public void add() {
        try {
            intBst.add(null);
        }
        catch (NullPointerException e) {}

        assertTrue(emptyIntBst.add(100));
        assertFalse(emptyIntBst.add(100));
        assertFalse(intBst.add(6));
    }

    @Test
    public void addAll() {
        try {
            emptyIntBst.addAll(null);
        }
        catch (NullPointerException e) {}

        try {
            emptyIntBst.addAll(intListWithNull);
        }
        catch (NullPointerException e) {}

        assertTrue(emptyIntBst.addAll(intList));
        assertFalse(emptyIntBst.addAll(intList));
        assertFalse(intBst.addAll(intList));
    }

    @Test
    public void clear() {
        randomIntBst.clear();
        assertTrue(randomIntBst.isEmpty());
        assertTrue(emptyIntBst.equals(randomIntBst));
    }

    @Test
    public void contains() {
        try {
            intBst.contains(null);
        }
        catch (NullPointerException e) {}

        // test the root, internal nodes and leaves
        assertTrue(intBst.contains(2));
        assertTrue(intBst.contains(6));
        assertTrue(intBst.contains(5));
        assertTrue(intBst.contains(7));
        assertFalse(intBst.contains(100));
    }

    @Test
    public void containsAll() {
        try {
            emptyIntBst.containsAll(null);
        }
        catch (NullPointerException e) {}

        try {
            emptyIntBst.containsAll(intListWithNull);
        }
        catch (NullPointerException e) {}

        assertFalse(emptyIntBst.containsAll(intList));
        assertTrue(intBst.containsAll(intList));

        intList.add(200);
        assertFalse(intBst.containsAll(intList));
    }

    @Test
    public void first() {
        try {
            emptyIntBst.first();
        }
        catch (NoSuchElementException e) {}

        int firstValue = intBst.first();
        assertEquals(1, firstValue);
    }

    @Test
    public void last() {
        try {
            emptyIntBst.last();
        }
        catch (NoSuchElementException e) {}

        int lastValue = intBst.last();
        assertEquals(7, lastValue);
    }

    @Test
    public void remove() {
        try {
            intBst.remove(null);
        }
        catch (NullPointerException e) {}

        assertTrue(intBst.remove(7));
        assertFalse(intBst.remove(7));
        assertFalse(emptyIntBst.remove(7));
    }

    @Test
    public void removeAll() {
        try {
            emptyIntBst.removeAll(null);
        }
        catch (NullPointerException e) {}

        try {
            emptyIntBst.removeAll(intListWithNull);
        }
        catch (NullPointerException e) {}

        assertFalse(emptyIntBst.removeAll(intList));
        assertTrue(intBst.removeAll(intList));

        intList.add(200);
        assertFalse(intBst.removeAll(intList));
    }

    @Test
    public void isEmpty() {
        assertTrue(emptyIntBst.isEmpty());
        assertFalse(intBst.isEmpty());
    }

    @Test
    public void size() {
        assertEquals(0, emptyIntBst.size());
        assertEquals(6, intBst.size());
        assertEquals(100, randomStrBst.size());
    }

    @Test
    public void equals() {
        assertTrue(intBst.equals(intBst));
        assertFalse(intBst.equals(randomIntBst));
        assertTrue(intBst.equals(intBstCopy));
    }

    @Test
    public void toArrayList() {
        assertEquals(randomIntBst.toArrayList().get(0), randomIntBst.first());
        assertEquals(randomIntBst.toArrayList().get(randomIntBst.size() - 1), randomIntBst.last());
        assertEquals(randomStrBst.toArrayList().get(0), randomStrBst.first());
        assertEquals(randomStrBst.toArrayList().get(randomStrBst.size() - 1), randomStrBst.last());
    }
}