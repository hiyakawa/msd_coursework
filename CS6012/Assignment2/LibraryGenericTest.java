/*
 * LibraryGenericTest.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 2: Generic Books
 * File 8 of 8
 */

package assignment02;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.GregorianCalendar;

import static org.junit.jupiter.api.Assertions.*;

class LibraryGenericTest {

    @Test
    public void stringLibraryTest() {
        // test a library that uses names (String) to id patrons
        LibraryGeneric<String> lib = new LibraryGeneric<>();
        lib.add(9780374292799L, "Thomas L. Friedman", "The World is Flat");
        lib.add(9780330351690L, "Jon Krakauer", "Into the Wild");
        lib.add(9780446580342L, "David Baldacci", "Simple Genius");

        String patron1 = "Jane Doe";

        assertTrue(lib.checkout(9780330351690L, patron1, 2008, 1, 1));
        assertTrue(lib.checkout(9780374292799L, patron1, 2008, 1, 1));

        var booksCheckedOut1 = lib.lookup(patron1);
        assertEquals(booksCheckedOut1.size(), 2);
        assertTrue(booksCheckedOut1.contains(new Book(9780330351690L, "Jon Krakauer", "Into the Wild")));
        assertTrue(booksCheckedOut1.contains(new Book(9780374292799L, "Thomas L. Friedman", "The World is Flat")));
        assertEquals(booksCheckedOut1.get(0).getHolder(), patron1);
        assertEquals(booksCheckedOut1.get(0).getDueDate(), new GregorianCalendar(2008, 1, 1));
        assertEquals(booksCheckedOut1.get(1).getHolder(),patron1);
        assertEquals(booksCheckedOut1.get(1).getDueDate(),new GregorianCalendar(2008, 1, 1));

        assertTrue(lib.checkin(patron1));
    }

    @Test
    public void phoneNumberTest(){
        // test a library that uses phone numbers (PhoneNumber) to id patrons
        var lib = new LibraryGeneric<PhoneNumber>();
        lib.add(9780374292799L, "Thomas L. Friedman", "The World is Flat");
        lib.add(9780330351690L, "Jon Krakauer", "Into the Wild");
        lib.add(9780446580342L, "David Baldacci", "Simple Genius");

        PhoneNumber patron2 = new PhoneNumber("801.555.1234");

        assertTrue(lib.checkout(9780330351690L, patron2, 2008, 1, 1));
        assertTrue(lib.checkout(9780374292799L, patron2, 2008, 1, 1));

        ArrayList<LibraryBookGeneric<PhoneNumber>> booksCheckedOut2 = lib.lookup(patron2);

        assertEquals(booksCheckedOut2.size(), 2);
        assertTrue(booksCheckedOut2.contains(new Book(9780330351690L, "Jon Krakauer", "Into the Wild")));
        assertTrue(booksCheckedOut2.contains(new Book(9780374292799L, "Thomas L. Friedman", "The World is Flat")));
        assertEquals(booksCheckedOut2.get(0).getHolder(),patron2);
        assertEquals(booksCheckedOut2.get(0).getDueDate(),new GregorianCalendar(2008, 1, 1));
        assertEquals(booksCheckedOut2.get(1).getHolder(), patron2);
        assertEquals(booksCheckedOut2.get(1).getDueDate(), new GregorianCalendar(2008, 1, 1));

        assertTrue(lib.checkin(patron2));
    }

    @Test
    public void sortingTest() {
        var libGen = new LibraryGeneric<PhoneNumber>();
        libGen.addAll("/Users/laurazhang/myLocalGithubRepo/CS6012/src/assignment02/Mushroom_Publishing.txt");

        var sortedLib = libGen.getInventoryList();

        for (LibraryBookGeneric<PhoneNumber> curBook : sortedLib) {
            System.out.println(curBook.getIsbn());
        }
    }
}