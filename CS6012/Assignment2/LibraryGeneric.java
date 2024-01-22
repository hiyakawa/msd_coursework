/*
 * LibraryGeneric.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 2: Generic Books
 * File 5 of 8
 */

package assignment02;

import java.io.File;
import java.io.FileNotFoundException;
import java.text.ParseException;
import java.util.*;

public class LibraryGeneric<Type> {
    private ArrayList<LibraryBookGeneric<Type>> library_;

    public LibraryGeneric() {
        library_ = new ArrayList<>();
    }

    public boolean checkin(Type patron1) {
        int checkInCounter = 0;
        // boolean instead

        for (LibraryBookGeneric<Type> curLibBook : library_) {
            if (Objects.equals(curLibBook.getHolder(), patron1)) {
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

    public boolean checkout(long isbn, Type patron2, int year, int month, int day) {
        for (LibraryBookGeneric<Type> curLibBook : library_) {
            if (curLibBook.getIsbn() == isbn) {
                // if the book with the specified ISBN is already checked out, returns false
                if (curLibBook.isCheckedOut()) {
                    return false;
                }

                // set the holder and due date of the library book with the specified ISBN
                curLibBook.setBookHolder(patron2);
                curLibBook.setDueDate(new GregorianCalendar(year, month, day));
                curLibBook.checkOut();

                return true;
            }
        }

        // if no book with the specified ISBN is in the library, returns false
        return false;
    }

    public ArrayList<LibraryBookGeneric<Type>> lookup(Type patron2) {
        ArrayList<LibraryBookGeneric<Type>> holdersBooks = new ArrayList<>();

        // get the list of library books checked out to the specified holder
        for (LibraryBookGeneric<Type> curBook : library_) {
            // compare the holder with the input holder
            if (curBook.getHolder().equals(patron2)) {
                holdersBooks.add(curBook);
            }
        }

        return holdersBooks;
    }

    public void add(long isbn, String author, String title) {
        library_.add(new LibraryBookGeneric<>(isbn, author, title));
    }

    /**
     * Returns the list of library books, sorted by ISBN (smallest ISBN first).
     */
    public ArrayList<LibraryBookGeneric<Type>> getInventoryList() {
        ArrayList<LibraryBookGeneric<Type>> libraryCopy = new ArrayList<>();
        libraryCopy.addAll(library_);

        OrderByIsbn comparator = new OrderByIsbn();

        sort(libraryCopy, comparator);

        return libraryCopy;
    }

    /**
     * Returns the list of library books, sorted by author
     */
    public ArrayList<LibraryBookGeneric<Type>> getOrderedByAuthor() {
        ArrayList<LibraryBookGeneric<Type>> libraryCopy = new ArrayList<>();
        libraryCopy.addAll(library_);

        OrderByAuthor comparator = new OrderByAuthor();
        sort(libraryCopy, comparator);

        return libraryCopy;
    }

    /**
     * Returns the list of library books whose due date is older than the input
     * date. The list is sorted by date (oldest first).
     * If no library books are overdue, returns an empty list.
     */
    public ArrayList<LibraryBookGeneric<Type>> getOverdueList(int month, int day, int year) {
        ArrayList<LibraryBookGeneric<Type>> overdueBooks = new ArrayList<>();
        GregorianCalendar dayToCompare = new GregorianCalendar(year, month, day);

        for (LibraryBookGeneric<Type> curBook : library_) {
            // compare the due date with the input date
            if (curBook.getDueDate().compareTo(dayToCompare) < 0) {
                overdueBooks.add(curBook);
            }
        }

        OrderByDueDate comparator = new OrderByDueDate();
        sort(overdueBooks, comparator);

        return overdueBooks;
    }

    /**
     * Performs a SELECTION SORT on the input ArrayList.
     *    1. Find the smallest item in the list.
     *    2. Swap the smallest item with the first item in the list.
     *    3. Now let the list be the remaining unsorted portion
     *       (second item to Nth item) and repeat steps 1, 2, and 3.
     */
    private static <ListType> void sort(ArrayList<ListType> list,
                                        Comparator<ListType> c) {
        for (int i = 0; i < list.size() - 1; i++) {
            int j, minIndex;
            for (j = i + 1, minIndex = i; j < list.size(); j++)
                if (c.compare(list.get(j), list.get(minIndex)) < 0)
                    minIndex = j;
            ListType temp = list.get(i);
            list.set(i, list.get(minIndex));
            list.set(minIndex, temp);
        }
    }

    /**
     * Comparator that defines an ordering among library books using the ISBN.
     */
    protected class OrderByIsbn implements Comparator<LibraryBookGeneric<Type>> {

        /**
         * Returns a negative value if lhs is smaller than rhs. Returns a positive
         * value if lhs is larger than rhs. Returns 0 if lhs and rhs are equal.
         */
        public int compare(LibraryBookGeneric<Type> lhs,
                           LibraryBookGeneric<Type> rhs) {
            return (int) (lhs.getIsbn() - rhs.getIsbn());
        }
    }

    /**
     * Comparator that defines an ordering among library books using the author, and book title as a tie-breaker.
     */
    protected class OrderByAuthor implements Comparator<LibraryBookGeneric<Type>> {
        /**
         * Returns a negative value if lhs is smaller than rhs. Returns a positive
         * value if lhs is larger than rhs. Returns 0 if lhs and rhs are equal.
         */
        public int compare(LibraryBookGeneric<Type> lhs,
                           LibraryBookGeneric<Type> rhs) {
            return (lhs.getAuthor().compareTo(rhs.getAuthor()));
        }
    }

    /**
     * Comparator that defines an ordering among library books using the due date.
     */
    protected class OrderByDueDate implements Comparator<LibraryBookGeneric<Type>> {
        /**
         * Returns a negative value if lhs is smaller than rhs. Returns a positive
         * value if lhs is larger than rhs. Returns 0 if lhs and rhs are equal.
         */
        public int compare(LibraryBookGeneric<Type> lhs,
                           LibraryBookGeneric<Type> rhs) {
            return (lhs.getDueDate().compareTo(rhs.getDueDate()));
        }
    }

    public void addAll(String filename) {
        ArrayList<LibraryBookGeneric<Type>> toBeAdded = new ArrayList<>();

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
                    toBeAdded.add(new LibraryBookGeneric<>(isbn, author, title));
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
}
