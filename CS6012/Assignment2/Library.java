/*
 * Library.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 2: Generic Books
 * File 2 of 8
 */

package assignment02;

import java.io.File;
import java.io.FileNotFoundException;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.GregorianCalendar;
import java.util.Objects;
import java.util.Scanner;

/**
 * Class representation of a library (a collection of library books).
 * 
 */
public class Library {
  private ArrayList<LibraryBook> library_;

  public Library() {
    library_ = new ArrayList<>();
  }

  /**
   * Add the specified book to the library, assume no duplicates.
   * 
   * @param isbn
   *          -- ISBN of the book to be added
   * @param author
   *          -- author of the book to be added
   * @param title
   *          -- title of the book to be added
   */
  public void add(long isbn, String author, String title) {
    library_.add(new LibraryBook(isbn, author, title));
  }

  /**
   * Add the list of library books to the library, assume no duplicates.
   * 
   * @param list
   *          -- list of library books to be added
   */
  public void addAll(ArrayList<LibraryBook> list) {
    library_.addAll(list);
  }

  /**
   * Add books specified by the input file. One book per line with ISBN, author,
   * and title separated by tabs.
   * 
   * If file does not exist or format is violated, do nothing.
   * 
   * @param filename
   */
  public void addAll(String filename) {
    ArrayList<LibraryBook> toBeAdded = new ArrayList<LibraryBook>();

    try (Scanner fileIn = new Scanner(new File(filename))) {

      int lineNum = 1;

      while (fileIn.hasNextLine()) {
        String line = fileIn.nextLine();

        try (Scanner lineIn = new Scanner(line)) {
          lineIn.useDelimiter("\\t");

          if (!lineIn.hasNextLong()) {
            throw new ParseException("ISBN", lineNum);
          }
          long isbn = lineIn.nextLong();

          if (!lineIn.hasNext()) {
            throw new ParseException("Author", lineNum);
          }
          String author = lineIn.next();

          if (!lineIn.hasNext()) {
            throw new ParseException("Title", lineNum);
          }
          String title = lineIn.next();
          toBeAdded.add(new LibraryBook(isbn, author, title));
        }
        lineNum++;
      }
    }
    catch (FileNotFoundException e) {
      System.err.println(e.getMessage() + " Nothing added to the library.");
      return;
    }
    catch (ParseException e) {
      System.err.println(e.getLocalizedMessage() + " formatted incorrectly at line " + e.getErrorOffset()
          + ". Nothing added to the library.");
      return;
    }

    library_.addAll(toBeAdded);
  }

  /**
   * Returns the holder of the library book with the specified ISBN.
   * 
   * If no book with the specified ISBN is in the library, returns null.
   * 
   * @param isbn
   *          -- ISBN of the book to be looked up
   */
  public String lookup(long isbn) {
    for (LibraryBook curLibBook : library_) {
      if (curLibBook.getIsbn() == isbn) {
        return curLibBook.getHolder();
      }
    }

    return null;
  }

  /**
   * Returns the list of library books checked out to the specified holder.
   * 
   * If the specified holder has no books checked out, returns an empty list.
   * 
   * @param holder
   *          -- holder whose checked out books are returned
   */
  public ArrayList<LibraryBook> lookup(String holder) {
    ArrayList<LibraryBook> holdersBooks = new ArrayList<>();

    for (LibraryBook curLibBook : library_) {
      if (Objects.equals(curLibBook.getHolder(), holder)) {
        holdersBooks.add(curLibBook);
      }
    }

    return holdersBooks;
  }

  public boolean checkout(long isbn, String holder, int year, int month, int day) {
    for (LibraryBook curLibBook : library_) {
      if (curLibBook.getIsbn() == isbn) {
        // if the book with the specified ISBN is already checked out, returns false
        if (curLibBook.isCheckedOut()) {
          return false;
        }

        // set the holder and due date of the library book with the specified ISBN
        curLibBook.setBookHolder(holder);
        curLibBook.setDueDate(new GregorianCalendar(year, month, day));
        curLibBook.checkOut();

        return true;
      }
    }

    // if no book with the specified ISBN is in the library, returns false
    return false;
  }

  public boolean checkin(long isbn) {
    for (LibraryBook curLibBook : library_) {
      if (curLibBook.getIsbn() == isbn) {
        // if the book with the specified ISBN is already checked in, returns false
        if (curLibBook.isCheckedIn()) {
          return false;
        }

        // unsets the holder and due date of the library book
        curLibBook.checkIn();
        return true;
      }
    }

    // if no book with the specified ISBN is in the library, returns false
    return false;
  }

  public boolean checkin(String holder) {
    int checkInCounter = 0;

    for (LibraryBook curLibBook : library_) {
      if (Objects.equals(curLibBook.getHolder(), holder)) {
        // unsets the holder and due date for all library books checked out by the specified holder
        curLibBook.checkIn();
        checkInCounter++;
      }
    }

    // if no book with the specified ISBN is in the library, returns false
    if (checkInCounter == 0) {
      return false;
    }

    return true;
  }
}
