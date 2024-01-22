/*
 * Book.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 2: Generic Books
 * File 1 of 8
 */

package assignment02;

/*
 * Class representation of a book. The ISBN, author, and title can never change
 * once the book is created.
 */

import java.util.Objects;

public class Book {
    private final long isbn;          // unique
    private final String author;
    private final String title;

    public Book(long isbn, String author, String title) {
        this.isbn = isbn;
        this.author = author;
        this.title = title;
    }

    public String getAuthor() {
        return this.author;
    }

    public long getIsbn() {
        return this.isbn;
    }

    public String getTitle() {
        return this.title;
    }

    public boolean equals(Object other) {
        if (!(other instanceof Book)) {
            // make sure the Object is a Book
            return false;
        }

        // if the above was not true, cast other to a Book
        Book rhsBook = (Book) other;

        // two books are considered equal if they have the same ISBN, author, and title
        return (isbn == rhsBook.isbn &&
                Objects.equals(author, rhsBook.author) &&
                Objects.equals(title, rhsBook.title));
    }

    public String toString() {
        return isbn + ", " + author + ", \"" + title + "\"";
    }

    @Override
    public int hashCode() {
        return (int) isbn + author.hashCode() + title.hashCode();
    }
}
