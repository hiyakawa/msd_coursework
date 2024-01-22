/*
 * LibraryBookGeneric.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 2: Generic Books
 * File 4 of 8
 */

package assignment02;

import java.util.GregorianCalendar;

public class LibraryBookGeneric<Type> extends Book {
    private Type bookHolder_;
    private GregorianCalendar dueDate_;
    private boolean checkedIn_;
    private boolean checkedOut_;
    // !! a book is either checked in or checked out

    public LibraryBookGeneric(long isbn, String author, String title) {
        super(isbn, author, title);
        checkedIn_ = false;
        checkedOut_ = false;
    }

    public Type getHolder() {
        return bookHolder_;
    }

    public GregorianCalendar getDueDate() {
        return dueDate_;
    }

    void checkIn() {
        // unsets the holder and due date of the library book
        bookHolder_ = null;
        dueDate_ = null;
        checkedIn_ = true;
    }

    void checkOut() {
        checkedOut_ = true;
    }

    public boolean isCheckedIn() {
        return checkedIn_;
    }

    public boolean isCheckedOut() {
        return checkedOut_;
    }

    //
    public void setBookHolder(Type holder) {
        bookHolder_ = holder;
    }

    public void setDueDate(GregorianCalendar dueDate) {
        dueDate_ = dueDate;
    }
}
