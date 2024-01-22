/*
 * QuadProbeHashTable.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 6: Hash Tables
 * File 6 of 6
 */

package assignment06;

import java.util.Collection;

public class QuadProbeHashTable implements Set<String> {
    /**
     * Constructs a hash table of the given capacity that uses the hashing function
     * specified by the given functor.
     */
    public QuadProbeHashTable(int capacity, HashFunctor functor) {

    }

    @Override
    public boolean add(String item) {
        return false;
    }

    @Override
    public boolean addAll(Collection<? extends String> items) {
        return false;
    }

    @Override
    public void clear() {

    }

    @Override
    public boolean contains(String item) {
        return false;
    }

    @Override
    public boolean containsAll(Collection<? extends String> items) {
        return false;
    }

    @Override
    public boolean isEmpty() {
        return false;
    }

    @Override
    public boolean remove(String item) {
        return false;
    }

    @Override
    public boolean removeAll(Collection<? extends String> items) {
        return false;
    }

    @Override
    public int size() {
        return 0;
    }
}
