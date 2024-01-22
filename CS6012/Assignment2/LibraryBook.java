/*
 * LibraryBook.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 2: Generic Books
 * File 3 of 8
 */

package assignment02;

import java.util.GregorianCalendar;

public class LibraryBook extends Book {
    private String bookHolder_;
    private GregorianCalendar dueDate_;
    private boolean checkedIn_;
    private boolean checkedOut_;

    public LibraryBook(long isbn, String author, String title) {
        super(isbn, author, title);
        checkedIn_ = false;
        checkedOut_ = false;
    }

    public String getHolder() {
        return bookHolder_;
    }

    public GregorianCalendar getDueDate() {
        return dueDate_;
    }

    public void checkIn() {
        // unsets the holder and due date of the library book
        bookHolder_ = null;
        dueDate_ = null;
        checkedIn_ = true;
    }

    public void checkOut() {
        checkedOut_ = true;
    }

    public boolean isCheckedIn() {
        return checkedIn_;
    }

    public boolean isCheckedOut() {
        return checkedOut_;
    }

    public void setBookHolder(String holder) {
        bookHolder_ = holder;
    }

    public void setDueDate(GregorianCalendar dueDate) {
        dueDate_ = dueDate;
    }
}
