/*
 * GoodHashFunctor.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 6: Hash Tables
 * File 3 of 6
 */

package assignment06;

public class GoodHashFunctor implements HashFunctor {
    /**
     * Implements djb2 algorithm.
     * Reference: <a href="http://www.cse.yorku.ca/~oz/hash.html">...</a>
     * @param item the string to be hashed
     * @return the index of the string after hashing
     */
    @Override
    public int hash(String item) {
        int hash = 5381;

        for (int charIndex = 0; charIndex < item.length(); charIndex++) {
            hash = (hash * 33) + (int) item.charAt(charIndex);
        }

        return hash;
    }
}
