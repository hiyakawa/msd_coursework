/*
 * ChainingHashTable.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 6: Hash Tables
 * File 1 of 6
 */

package assignment06;

import java.util.Collection;
import java.util.LinkedList;
import static java.lang.Math.abs;

public class ChainingHashTable implements Set<String> {
    private LinkedList<String>[] storage_;
    private int size_;
    private int capacity_;
    private HashFunctor functor_;
    private static final double LOAD_FACTOR = 0.75;

    @SuppressWarnings("unchecked")
    public ChainingHashTable(int capacity, HashFunctor functor) {
        if (capacity <= 0 || functor == null) {
            throw new IllegalArgumentException();
        }

        size_ = 0;
        capacity_ = capacity;
        functor_ = functor;
        storage_ = (LinkedList<String>[]) new LinkedList[capacity_];

        for (int i = 0; i < capacity; i++) {
            storage_[i] = new LinkedList<>();
        }
    }

    /**
     * Ensures that this set contains the specified item.
     * @param item the item whose presence is ensured in this set
     * @return true if this set changed as a result of this method call
     * (that is, if the input item was actually inserted);
     * otherwise, returns false
     */
    @Override
    public boolean add(String item) {
        if (item == null) {
            throw new NullPointerException();
        }

        if (! this.contains(item)) {
            int index = hashIndex(item);
            index += index < 0 ? capacity_ : 0;
            storage_[index].add(item);
            size_++;
            growTable();

            return true;
        }
        return false;
    }

    /**
     * Ensures that this set contains all items in the specified collection.
     * @param items the collection of items whose presence is ensured in this set
     * @return true if this set changed as a result of this method call
     * (that is, if any item in the input collection was actually inserted);
     * otherwise, returns false
     */
    @Override
    public boolean addAll(Collection<? extends String> items) {
        if (items != null) {
            int originalSize = size_;

            for (String curStr : items) {
                if (curStr == null) {
                    throw new NullPointerException();
                }
                this.add(curStr);
            }
            return size_ != originalSize;
        }
        else {
            throw new NullPointerException();
        }
    }

    /**
     * Removes all items from this hash table. The hash table will be empty after this method call.
     */
    @Override
    public void clear() {
        for (int i = 0; i < capacity_; i++) {
            storage_[i] = new LinkedList<>();
        }
        size_ = 0;
    }

    /**
     * Determines if there is an item in this set that is equal to the specified item.
     * @param item the item sought in this set
     * @return true if there is an item in this set that is equal to the input item; otherwise, returns false
     */
    @Override
    public boolean contains(String item) {
        if (item == null) {
            throw new NullPointerException();
        }

        int index = hashIndex(item);
        return storage_[index].contains(item);
    }

    /**
     * Determines if for each item in the specified collection, there is an item in this set that is equal to it.
     * @param items the collection of items sought in this set
     * @return true if for each item in the specified collection, there is an item in this set that is equal to it;
     * otherwise, returns false
     */
    @Override
    public boolean containsAll(Collection<? extends String> items) {
        if (items != null) {
            for (String curStr : items) {
                if (curStr == null) {
                    throw new NullPointerException();
                }

                if (! this.contains(curStr)) {
                    return false;
                }
            }
            return true;
        }
        else {
            throw new NullPointerException();
        }
    }

    /**
     * Returns true if this hash table contains no items.
     */
    @Override
    public boolean isEmpty() {
        return size_ == 0;
    }

    /**
     * Ensures that this set does not contain the specified item.
     * @param item the item whose absence is ensured in this set
     * @return true if this set changed as a result of this method call
     * (that is, if the input item was actually removed);
     * otherwise, returns false
     */
    @Override
    public boolean remove(String item) {
        if (item != null) {
            int index = hashIndex(item);

            if (storage_[index].remove(item)) {
                size_--;
                return true;
            }
            return false;
        }
        else {
            throw new NullPointerException();
        }
    }

    /**
     * Ensures that this set does not contain any of the items in the specified collection.
     * @param items the collection of items whose absence is ensured in this set
     * @return true if this set changed as a result of this method call
     * (that is, if any item in the input collection was actually removed);
     * otherwise, returns false
     */
    @Override
    public boolean removeAll(Collection<? extends String> items) {
        if (items != null) {
            int originalSize = size_;

            for (String curStr : items) {
                if (curStr == null) {
                    throw new NullPointerException();
                }
                this.remove(curStr);
            }
            return size_ != originalSize;
        }
        else {
            throw new NullPointerException();
        }
    }

    /**
     * Returns the number of items in this hash table.
     */
    @Override
    public int size() {
        return size_;
    }

    /**
     * Allocates new capacity for the hash table
     * if size divided by capacity hits the resize factor.
     */
    private void growTable() {
        if (size_ >= LOAD_FACTOR * capacity_) {
            capacity_ *= 2;
            ChainingHashTable newTable = new ChainingHashTable(capacity_, functor_);

            for (LinkedList<String> curList : storage_) {
                for (String curStr : curList) {
                    newTable.add(curStr);
                }
            }
            storage_ = newTable.storage_;
        }
    }

    /**
     * Prints each bucket in the hash table with the index numbers.
     */
    public void printTable() {
        for (LinkedList<String> curList : storage_) {
            for (String curStr : curList) {
                System.out.println(hashIndex(curStr) + "\t" + curStr);
            }
        }
        System.out.println("");
    }

    /**
     * Returns the bucket index after hashing.
     */
    private int hashIndex(String item) {
        return abs(functor_.hash(item) % capacity_);
    }
}