/*
 * BinarySearchSetTest.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 3: Searching a Set
 * File 2 of 2
 */

package assignment03;

import assignment02.Book;
import assignment02.LibraryBookGeneric;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import java.util.*;
import static org.junit.Assert.*;

class BinarySearchSetTest {
    BinarySearchSet<Integer> ascendingIntSet;
    BinarySearchSet<Integer> descendingIntSet;
    BinarySearchSet<Integer> emptyIntSet;

    BinarySearchSet<Integer> randomIntSet;
    BinarySearchSet<Character> randomCharSet;
    BinarySearchSet<String> randomStrSet;

    BinarySearchSet<Book> bookSet;
    Comparator<Book> bookComparator;

    Collection<Integer> intCollection;
    Collection<Integer> smallIntCollection;
    Collection<Integer> emptyIntCollection;

    @BeforeEach
    public void setUp() {
        ascendingIntSet = new BinarySearchSet<>();
        descendingIntSet = new BinarySearchSet<>();
        emptyIntSet = new BinarySearchSet<>();

        randomIntSet = new BinarySearchSet<>();
        randomCharSet = new BinarySearchSet<>();
        randomStrSet = new BinarySearchSet<>();

        bookSet = new BinarySearchSet<>(bookComparator);

        intCollection = new ArrayList<>();
        smallIntCollection = new ArrayList<>();
        emptyIntCollection = new ArrayList<>();

        for (int i = 0; i < 100; i++) {
            ascendingIntSet.add(i);
        }

        for (int i = 100; i > 0; i--) {
            descendingIntSet.add(i);
        }

        for (int i = 0; i < 102; i++) {
            intCollection.add(i);
        }

        for (int i = 0; i < 10; i++) {
            smallIntCollection.add(i);
        }

        for (int i = 0; i < 100; i++) {
            Random rand = new Random();
            int randInt = rand.nextInt(100);
            randomIntSet.add(randInt);
        }

        for (int i = 0; i < 26; i++) {
            Random rand = new Random();
            char randChar = (char)(rand.nextInt(26) + 'a');
            randomCharSet.add(randChar);
            randChar = (char)(rand.nextInt(26) + 'A');
            randomCharSet.add(randChar);
        }

        for (int i = 0; i < 50; i++) {
            Random rand = new Random();
            String randStr = "";
            int randInt = rand.nextInt(10) + 1;

            for (int j = 0; j < randInt; j++) {
                randStr += (char) (rand.nextInt(26) + 'a');
                randStr += (char) (rand.nextInt(26) + 'A');
            }

            randomStrSet.add(randStr);
        }
    }

    @Test
    public void addAscendingArrayTest() {
        assertEquals(100, ascendingIntSet.size());
        assertEquals(128, ascendingIntSet.getCapacity());
    }

    @Test
    public void addAllAscendingArrayTest() {
        // adding all from null
        assertFalse(ascendingIntSet.addAll(null));
        assertEquals(100, ascendingIntSet.size());

        // adding all elements from an array
        assertTrue(ascendingIntSet.addAll(intCollection));
        assertEquals(102, ascendingIntSet.size());

        // adding all from an empty array
        assertFalse(ascendingIntSet.addAll(emptyIntCollection));
        assertEquals(102, ascendingIntSet.size());

        // adding all existing elements from an array
        assertFalse(ascendingIntSet.addAll(intCollection));
        assertEquals(102, ascendingIntSet.size());
    }

    @Test
    public void addDescendingArrayTest() {
        assertEquals(100, descendingIntSet.size());
        assertEquals(128, descendingIntSet.getCapacity());
    }

    @Test
    public void randomIntArrayTest() {
        randomIntSet.printArray();
        System.out.println(randomIntSet.size());
        System.out.println(randomIntSet.getCapacity());
    }

    @Test
    public void randomCharArrayTest() {
        randomCharSet.printArray();
        System.out.println(randomCharSet.size());
        System.out.println(randomCharSet.getCapacity());
    }

    @Test
    public void randomStrArrayTest() {
        randomStrSet.printArray();
        System.out.println(randomStrSet.size());
        System.out.println(randomStrSet.getCapacity());
    }

    @Test
    public void firstAndLastTest() {
        try {
            System.out.println(emptyIntSet.first());
        }
        catch (NoSuchElementException e) {
            System.out.println("exception caught");
        }

        try {
            System.out.println(emptyIntSet.last());
        }
        catch (NoSuchElementException e) {
            System.out.println("exception caught");
        }
    }

    @Test
    public void containsTest() {
        assertTrue(ascendingIntSet.contains(0));
        assertTrue(ascendingIntSet.contains(99));
        assertFalse(ascendingIntSet.contains(200));
        assertFalse(ascendingIntSet.contains(null));
    }

    @Test
    public void containsAllTest() {
        assertTrue(ascendingIntSet.containsAll(emptyIntCollection));
        assertTrue(ascendingIntSet.containsAll(smallIntCollection));
        assertFalse(ascendingIntSet.containsAll(intCollection));
        assertFalse(ascendingIntSet.containsAll(null));
    }

    @Test
    public void removeTest() {
//        ascendingIntSet.iterator().remove();

        assertTrue(ascendingIntSet.remove(0));
        assertFalse(ascendingIntSet.remove(100));

        try {
            ascendingIntSet.remove(null);
        }
        catch (Exception e) {}
    }

    @Test
    public void removeAllTest() {
        assertTrue(ascendingIntSet.removeAll(smallIntCollection));
        assertTrue(ascendingIntSet.removeAll(intCollection));
        assertFalse(ascendingIntSet.removeAll(smallIntCollection));
        assertFalse(ascendingIntSet.removeAll(null));
    }

    @Test
    public void isEmptyTest() {
        assertTrue(emptyIntSet.isEmpty());
        assertFalse(randomCharSet.isEmpty());
    }

    @Test
    public void clearTest() {
        ascendingIntSet.clear();
        assertEquals(0, ascendingIntSet.size());
        assertEquals(8, ascendingIntSet.getCapacity());

        try {
            System.out.println(ascendingIntSet.last());
        }
        catch (NoSuchElementException expectedException) {
            System.out.println("exception caught");
        }
    }

    @Test
    public void toArrayTest() {
        Integer[] copy = new Integer[128];

        for (int i = 0; i < 100; i++) {
            copy[i] = i;
        }

        assertArrayEquals(copy, ascendingIntSet.toArray());
    }

    @Test
    public void iteratorTest() {
        Iterator<Integer> iter = ascendingIntSet.iterator();
        assertTrue(iter.hasNext());

        iter = emptyIntSet.iterator();
        assertFalse(iter.hasNext());
        try {
            iter.next();
        }
        catch (NoSuchElementException e) {}
    }

    @Test
    public void bookArrayTest(){
        LibraryBookGeneric<String> book1 = new LibraryBookGeneric<>
                (9780330351690L, "Jon Krakauer", "Into the Wild");
        LibraryBookGeneric<String> book2 = new LibraryBookGeneric<>
                (9780374292799L, "Thomas L. Friedman", "The World is Flat");
        LibraryBookGeneric<String> book3 = new LibraryBookGeneric<>
                (9780446580342L, "David Baldacci", "Simple Genius");

        BookIsbnComparator bookComparator = new BookIsbnComparator();
        BinarySearchSet<LibraryBookGeneric<String>> bookSet = new BinarySearchSet<>(bookComparator);

        assertTrue(bookSet.isEmpty());
        assertTrue(bookSet.add(book1));
        assertTrue(bookSet.add(book2));
        assertTrue(bookSet.add(book3));
        assertFalse(bookSet.add(book1));
        assertEquals(book1, bookSet.first());
        assertEquals(book3, bookSet.last());
    }

    public static class BookIsbnComparator implements Comparator<LibraryBookGeneric<String>> {
        public int compare(LibraryBookGeneric<String> lhs, LibraryBookGeneric<String> rhs) {
            return (int) (lhs.getIsbn() - rhs.getIsbn());
        }
    }
//
//    @Test
//    public void containsTimer() {
//        int times = 1000;
//        long startTime = System.nanoTime();
//        while (System.nanoTime() - startTime < 1_000_000_000);
//
//        for (int exp = 10; exp < 26; exp++) {
//            int size = (int) Math.pow(2, exp);
//            long totalTime = 0;
//
//            BinarySearchSet <Integer> intSet = new BinarySearchSet<>();
//            for (int i = 0; i < size; i++) {
//                intSet.add(i);
//            }
//
//            Random rand = new Random();
//            for (int i = 0; i < times; i++) {
//                int element = rand.nextInt(size);
//                long curStartTime = System.nanoTime();
//                intSet.contains(element);
//                long curStopTime = System.nanoTime();
//                totalTime += (curStopTime - curStartTime);
//            }
//
//            double averageTime = totalTime / (double) times;
//            System.out.println(size + " " + averageTime);
//        }
//    }
//
//    @Test
//    public void addTimer() {
//        int times = 1000;
//        long startTime = System.nanoTime();
//        while (System.nanoTime() - startTime < 1_000_000_000);
//
//        for (int exp = 10; exp < 26; exp++) {
//            int size = (int) Math.pow(2, exp);
//            long totalTime = 0;
//
//            BinarySearchSet <Integer> intSet = new BinarySearchSet<>();
//            for (int i = 0; i < size; i++) {
//                intSet.add(i);
//            }
//
//            Random rand = new Random();
//            for (int i = 0; i < times; i++) {
//                int element = rand.nextInt(size);
//                intSet.remove(element);
//                long curStartTime = System.nanoTime();
//                intSet.add(element);
//                long curStopTime = System.nanoTime();
//                totalTime += (curStopTime - curStartTime);
//            }
//
//            double averageTime = totalTime / (double) times;
//            System.out.println(size + " " + averageTime);
//        }
//    }
}