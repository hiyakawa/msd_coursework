/*
 * BadHashFunctor.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 6: Hash Tables
 * File 5 of 6
 */

package assignment06;

public class BadHashFunctor implements HashFunctor {
    /**
     * Implements lose lose algorithm appeared in K&R (1st ed).
     * Returns the summation of all bytes in the string.
     * Reference: <a href="http://www.cse.yorku.ca/~oz/hash.html">...</a>
     * @param item the string to be hashed
     * @return the index of the string after hashing
     */
    @Override
    public int hash(String item) {
        int hash = 0;

        for (int charIndex = 0; charIndex < item.length(); charIndex++) {
            hash += item.charAt(charIndex);
        }

        return hash;
    }
}
