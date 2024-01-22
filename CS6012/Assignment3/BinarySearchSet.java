/*
 * BinarySearchSet.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 3: Searching a Set
 * File 1 of 2
 */

package assignment03;

import java.util.*;

public class BinarySearchSet<E> implements SortedSet<E>, Iterable<E> {
    private E[] set_;
    private int size_;
    private int capacity_;
    private Comparator<? super E> comparator_;

    public BinarySearchSet() {
        size_ = 0;
        capacity_ = 8;
        set_ = (E[]) new Object[capacity_];
        comparator_ = null;
    }

    public BinarySearchSet(Comparator<? super E> comparator) {
        size_ = 0;
        capacity_ = 8;
        set_ = (E[]) new Object[capacity_];
        comparator_ = comparator;
    }

    /**
     * @return The comparator used to order the elements in this set, or null if
     *         this set uses the natural ordering of its elements (i.e., uses
     *         Comparable).
     */
    @Override
    public Comparator<? super E> comparator() {
        return comparator_;
    }

    /**
     * @return the first (lowest, smallest) element currently in this set
     * @throws NoSuchElementException if the set is empty
     */
    @Override
    public E first() throws NoSuchElementException {
        if (size_ == 0) {
            throw new NoSuchElementException("The set is empty");
        }

        return set_[0];
    }

    /**
     * @return the last (highest, largest) element currently in this set
     * @throws NoSuchElementException if the set is empty
     */
    @Override
    public E last() throws NoSuchElementException {
        if (size_ == 0) {
            throw new NoSuchElementException("The set is empty");
        }

        return set_[size_ - 1];
    }

    /**
     * Adds the specified element to this set if it is not already present and
     * not set to null.
     *
     * @param  element element to be added to this set
     * @return true if this set did not already contain the specified element
     */
    @Override
    public boolean add(E element) {
        try {
            // base case: starting from an empty set
            if (size_ == 0) {
                set_[0] = element;
                size_++;
                growSet();
                return true;
            }

            // binary insertion sort
            int low = 0;
            int high = size_ - 1;

            while (low <= high) {
                int mid = (low + high) / 2;

                if (compare(element, set_[mid]) < 0) {
                    high = mid - 1;
                } else if (compare(element, set_[mid]) == 0) {
                    // if the input element is found
                    return false;
                } else {
                    low = mid + 1;
                }
            }

            // backward shift
            for (int j = size_ - 1; j >= low; j--) {
                set_[j + 1] = set_[j];
            }

            // insert the input element
            set_[low] = element;
            size_++;
            growSet();
            return true;
        }
        catch (NullPointerException e) {
            return false;
        }
    }

    /**
     * Adds all of the elements in the specified collection to this set if they
     * are not already present and not set to null.
     *
     * @param elements collection containing elements to be added to this set
     * @return true if this set changed as a result of the call
     */
    @Override
    public boolean addAll(Collection<? extends E> elements) {
        try {
            int originalSize = size_;

            for (E element : elements) {
                this.add(element);
            }

            return size_ != originalSize;
        }
        catch (NullPointerException e) {
            return false;
        }
    }

    /**
     * Removes all of the elements from this set. The set will be empty after
     * this call returns.
     */
    @Override
    public void clear() {
        size_ = 0;
        capacity_ = 8;
        set_ = (E[]) (new Object[capacity_]);
    }

    /**
     * @param element element whose presence in this set is to be tested
     * @return true if this set contains the specified element
     */
    @Override
    public boolean contains(E element) {
        try {
            // binary search
            int low = 0;
            int high = size_ - 1;

            while (low <= high) {
                int mid = (high + low) / 2;

                if (compare(element, set_[mid]) == 0) {
                    // if the input element is found
                    return true;
                }
                else if (compare(element, set_[mid]) > 0) {
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
            }

            return false;
        }
        catch (NullPointerException e) {
            return false;
        }
    }

    /**
     * @param elements collection to be checked for containment in this set
     * @return true if this set contains all of the elements of the specified
     *         collection
     */
    @Override
    public boolean containsAll(Collection<? extends E> elements) {
        try {
            for (E element : elements) {
                if (! this.contains(element)) {
                    return false;
                }
            }

            return true;
        }
        catch (NullPointerException e) {
            return false;
        }
    }

    /**
     * @return true if this set contains no elements
     */
    @Override
    public boolean isEmpty() {
        return size_ == 0;
    }

    @Override
    public Iterator<E> iterator() {
        return new BinarySearchSetIterator<>();
    }

    /**
     * @return an iterator over the elements in this set, where the elements are
     *         returned in sorted (ascending) order
     */
    private class BinarySearchSetIterator<E> implements Iterator<E> {
        private int position = 0;

        @Override
        public boolean hasNext() {
            return position < size_ && set_[position] != null;
        }

        @Override
        public E next() {
            if (hasNext()) {
                return (E) set_[position++];
            }
            throw new NoSuchElementException();
        }

        @Override
        public void remove() {
//            BinarySearchSet.this.remove(set_[position]);
//            position--;
            throw new UnsupportedOperationException();
        }
    }

    /**
     * Removes the specified element from this set if it is present.
     *
     * @param element element to be removed from this set, if present
     * @return true if this set contained the specified element
     */
    @Override
    public boolean remove(E element) {
        try {
            // for an empty set, return false
            if (size_ == 0) {
                return false;
            }

            // binary insertion sort
            int low = 0;
            int high = size_ - 1;

            while (low <= high) {
                int mid = (low + high) / 2;

                if (compare(element, set_[mid]) < 0) {
                    high = mid - 1;
                }
                else if (compare(element, set_[mid]) == 0) {
                    // if the input element is found, forward shift
                    for (int i = mid; i < size_; i++) {
                        set_[i] = set_[i + 1];
                    }

                    size_--;
                    return true;
                }
                else {
                    low = mid + 1;
                }
            }
            return false;
        }
        catch (Exception e) {
            throw new UnsupportedOperationException();
        }
    }

    /**
     * Removes from this set all of its elements that are contained in the
     * specified collection.
     *
     * @param elements collection containing elements to be removed from this set
     * @return true if this set changed as a result of the call
     */
    @Override
    public boolean removeAll(Collection<? extends E> elements) {
        try {
            int originalSize = size_;

            for (E element : elements) {
                this.remove(element);
            }

            return size_ != originalSize;
        }
        catch (NullPointerException e) {
            return false;
        }
    }

    /**
     * @return the number of elements in this set
     */
    @Override
    public int size() {
        return size_;
    }

    /**
     * @return an array containing all of the elements in this set, in sorted
     *         (ascending) order.
     */
    @Override
    public E[] toArray() {
        E[] arr = (E[]) new Object[capacity_];

        for (int i = 0; i < size_; i++) {
            arr[i] = set_[i];
        }

        return arr;
    }

    private int compare(E lhs, E rhs) {
        if (comparator_ != null) {
            return comparator_.compare(lhs, rhs);
        }

        return ((Comparable<? super E>) lhs).compareTo(rhs);
    }

    public int getCapacity() {
        return capacity_;
    }

    public void printArray() {
        try {
            for (int i = 0; i < size_; i++) {
                System.out.println(set_[i]);
            }
        }
        catch (Exception e) {
            System.out.println("not able to print the elements");
        }
    }

    private void growSet() {
        if (size_ >= capacity_) {
            E[] tempSet = (E[]) new Object[size_ * 2];

            for (int i = 0; i < size_; i++) {
                tempSet[i] = set_[i];
            }

            capacity_ = size_ * 2;

            set_ = tempSet;
            tempSet = null;
        }
    }
}
