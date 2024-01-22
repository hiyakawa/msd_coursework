/*
 * MediocreHashFunctor.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 6: Hash Tables
 * File 4 of 6
 */

package assignment06;

public class MediocreHashFunctor implements HashFunctor {
    /**
     * Implements K&R algorithm appeared in K&R (2nd ed) and is slightly modified.
     * It's basically the same as djb2 algorithm, but the initial value of hash
     * is set to 0 and each time hash is multiplied by 10.
     * Reference: <a href="https://stackoverflow.com/questions/7666509/hash-function-for-string">...</a>
     * @param item the string to be hashed
     * @return the index of the string after hashing
     */
    @Override
    public int hash(String item) {
        int hash = 0;

        for (int charIndex = 0; charIndex < item.length(); charIndex++) {
            hash = (hash * 10) + (int) item.charAt(charIndex);
        }

        return hash;
    }
}
