/*
 * LibraryTest.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 2: Generic Books
 * File 7 of 8
 */

package assignment02;

import org.junit.jupiter.api.Test;
import java.util.ArrayList;
import java.util.GregorianCalendar;
import static org.junit.jupiter.api.Assertions.*;

class LibraryTest {
    @Test
    public void testEmpty() {
        Library lib = new Library();
        assertNull(lib.lookup(978037429279L));

        ArrayList<LibraryBook> booksCheckedOut = lib.lookup("Jane Doe");
        assertEquals(booksCheckedOut.size(), 0);

        assertFalse(lib.checkout(978037429279L, "Jane Doe", 2008, 1, 1));
        assertFalse(lib.checkin(978037429279L));
        assertFalse(lib.checkin("Jane Doe"));
    }

    @Test
    public void testNonEmpty() {
        var lib = new Library();
        // test a small library
        lib.add(9780374292799L, "Thomas L. Friedman", "The World is Flat");
        lib.add(9780330351690L, "Jon Krakauer", "Into the Wild");
        lib.add(9780446580342L, "David Baldacci", "Simple Genius");

        assertNull(lib.lookup(9780330351690L)); // not checked out
        var res = lib.checkout(9780330351690L, "Jane Doe", 2008, 1, 1);
        assertTrue(res);
        var booksCheckedOut = lib.lookup("Jane Doe");
        assertEquals(booksCheckedOut.size(), 1);
        assertEquals(booksCheckedOut.get(0), new Book(9780330351690L, "Jon Krakauer", "Into the Wild"));
        assertEquals(booksCheckedOut.get(0).getHolder(), "Jane Doe");
        assertEquals(booksCheckedOut.get(0).getDueDate(), new GregorianCalendar(2008, 1, 1));

        res = lib.checkin(9780330351690L);
        assertTrue(res);
        res = lib.checkin("Jane Doe");
        assertFalse(res);

        // test for another book
        assertNull(lib.lookup(9780374292799L)); // not checked out
        res = lib.checkout(9780374292799L, "Alex Lee", 2008, 1, 1);
        assertTrue(res);
        booksCheckedOut = lib.lookup("Alex Lee");
        assertEquals(booksCheckedOut.size(), 1);
        assertEquals(booksCheckedOut.get(0), new Book(9780374292799L, "Thomas L. Friedman", "The World is Flat"));
        assertEquals(booksCheckedOut.get(0).getHolder(), "Alex Lee");
        assertEquals(booksCheckedOut.get(0).getDueDate(), new GregorianCalendar(2008, 1, 1));

        res = lib.checkin(9780374292799L);
        assertTrue(res);
        res = lib.checkin("Alex Lee");
        assertFalse(res);
    }

    @Test
    public void testLargeLibrary(){
        // test a medium library
        var lib = new Library();
        lib.addAll("/Users/laurazhang/myLocalGithubRepo/CS6012/src/assignment02/Mushroom_Publishing.txt");

//        assertNull(lib.lookup(9780374292799L)); // not checked out
//        var res = lib.checkout(9780374292799L, "Alex Lee", 2008, 1, 1);
//        assertTrue(res);
//        var booksCheckedOut = lib.lookup("Alex Lee");
//        assertEquals(booksCheckedOut.size(), 1);
//        assertEquals(booksCheckedOut.get(0), new Book(9780374292799L, "Thomas L. Friedman", "The World is Flat"));
//        assertEquals(booksCheckedOut.get(0).getHolder(), "Alex Lee");
//        assertEquals(booksCheckedOut.get(0).getDueDate(), new GregorianCalendar(2008, 1, 1));
//
//        res = lib.checkin(9780374292799L);
//        assertTrue(res);
//        res = lib.checkin("Alex Lee");
//        assertFalse(res);
    }

}