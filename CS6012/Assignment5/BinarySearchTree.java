/*
 * BinarySearchTree.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 5: Binary Search Trees
 * File 1 of 3
 */

package assignment05;

import java.util.*;

public class BinarySearchTree<T extends Comparable<? super T>> implements SortedSet<T> {
    private Node root_;
    private int size_;

    public BinarySearchTree() {
        root_ = null;
        size_ = 0;
    }

    class Node {
        T value_;
        Node left_, right_;

        public Node(T value) {
            value_ = value;
            left_ = null;
            right_ = null;
        }
    }

    /**
     * Ensures that this set contains the specified item.
     * @param item the item whose presence is ensured in this set
     * @return true if this set changed as a result of this method call
     * (that is, if the input item was actually inserted); otherwise, returns false
     * @throws NullPointerException if the item is null
     */
    @Override
    public boolean add(T item) {
        if (item != null) {
            Node prev = null;
            Node curNode = root_;
            int cmp = 0;

            while (curNode != null) {
                cmp = curNode.value_.compareTo(item);

                if (cmp == 0) {
                    return false;
                }

                prev = curNode;
                if (cmp < 0) {
                    curNode = curNode.right_;
                }
                else {
                    curNode = curNode.left_;
                }
            }

            if (prev == null) {
                root_ = new Node(item);
            }
            else {
                // value of current node is less than input value
                if (cmp < 0) {
                    prev.right_ = new Node(item);
                }
                else {
                    prev.left_ = new Node(item);
                }
            }
        }
        else {
            throw new NullPointerException();
        }

        updateSize(root_);
        return true;
    }

    /**
     * Ensures that this set contains all items in the specified collection.
     * @param items the collection of items whose presence is ensured in this set
     * @return true if this set changed as a result of this method call
     * (that is, if any item in the input collection was actually inserted); otherwise, returns false
     * @throws NullPointerException if any of the items is null
     */
    @Override
    public boolean addAll(Collection<? extends T> items) {
        if (items != null) {
            int originalSize = size_;

            for (T item : items) {
                if (item == null) {
                    throw new NullPointerException();
                }
                this.add(item);
            }
            return size_ != originalSize;
        }
        else {
            throw new NullPointerException();
        }
    }

    /**
     * Removes all items from this set. The set will be empty after this method call.
     */
    @Override
    public void clear() {
        root_ = null;
        size_ = 0;
    }

    /**
     * Determines if there is an item in this set that is equal to the specified item.
     * @param item the item sought in this set
     * @return true if there is an item in this set that is equal to the input item; otherwise, returns false
     * @throws NullPointerException if the item is null
     */
    @Override
    public boolean contains(T item) {
        if (item != null) {
            Node curNode = root_;

            while (curNode != null) {
                if (curNode.value_.compareTo(item) == 0) {
                    return true;
                }
                else if (curNode.value_.compareTo(item) < 0) {
                    curNode = curNode.right_;
                }
                else {
                    curNode = curNode.left_;
                }
            }
        }
        else {
            throw new NullPointerException();
        }

        return false;
    }

    /**
     * Determines if for each item in the specified collection, there is an item in this set that is equal to it.
     * @param items the collection of items sought in this set
     * @return true if for each item in the specified collection, there is an item in this set that is equal to it;
     * otherwise, returns false
     * @throws NullPointerException if any of the items is null
     */
    @Override
    public boolean containsAll(Collection<? extends T> items) {
        if (items != null) {
            for (T item : items) {
                if (item == null) {
                    throw new NullPointerException();
                }

                if (! this.contains(item)) {
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
     * Returns the first (i.e., smallest) item in this set.
     * @throws NoSuchElementException if the set is empty
     */
    @Override
    public T first() throws NoSuchElementException {
        if (! this.isEmpty()) {
            Node minNode = root_;

            while (minNode.left_ != null) {
                minNode = minNode.left_;
            }

            return minNode.value_;
        }
        else {
            throw new NoSuchElementException();
        }
    }

    /**
     * Returns the last (i.e., largest) item in this set.
     * @throws NoSuchElementException if the set is empty
     */
    @Override
    public T last() throws NoSuchElementException {
        if (! this.isEmpty()) {
            Node maxNode = root_;

            while (maxNode.right_ != null) {
                maxNode = maxNode.right_;
            }

            return maxNode.value_;
        }
        else {
            throw new NoSuchElementException();
        }
    }

    /**
     * Ensures that this set does not contain the specified item.
     * @param item the item whose absence is ensured in this set
     * @return true if this set changed as a result of this method call
     * (that is, if the input item was actually removed); otherwise, returns false
     * @throws NullPointerException if the item is null
     */
    @Override
    public boolean remove(T item) {
        if (item != null) {
            Node prev = null;
            Node curNode = root_;

            while (curNode != null &&
                   curNode.value_.compareTo(item) != 0) {
                prev = curNode;

                if (item.compareTo(curNode.value_) < 0) {
                    curNode = curNode.left_;
                }
                else {
                    curNode = curNode.right_;
                }
            }

            // the input value is not found
            if (curNode == null) {
                return false;
            }

            // if current node is an internal node with two children
            if (curNode.right_ != null && curNode.left_ != null) {
                Node successor = curNode.right_;
                Node ptr = null;

                while (successor.left_ != null) {
                    ptr = successor;
                    successor = successor.left_;
                }

                if (ptr == null) {
                    curNode.right_ = successor.right_;
                }
                else {
                    ptr.left_ = successor.right_;
                }

                curNode.value_ = successor.value_;
            }
            else {
                Node newCurr = null;

                if (curNode.left_ != null) {
                    newCurr = curNode.left_;
                }
                else if (curNode.right_ != null) {
                    newCurr = curNode.right_;
                }

                if (prev == null) {
                    root_ = newCurr;
                }
                else {
                    if (prev.right_ == curNode) {
                        prev.right_ = newCurr;
                    }
                    else {
                        prev.left_ = newCurr;
                    }
                }
            }
        }
        else {
            throw new NullPointerException();
        }

        updateSize(root_);
        return true;
    }

    /**
     * Ensures that this set does not contain any of the items in the specified collection.
     * @param items the collection of items whose absence is ensured in this set
     * @return true if this set changed as a result of this method call
     * (that is, if any item in the input collection was actually removed); otherwise, returns false
     * @throws NullPointerException if any of the items is null
     */
    @Override
    public boolean removeAll(Collection<? extends T> items) {
        try {
            int originalSize = size_;

            for (T item : items) {
                this.remove(item);
            }

            return size_ != originalSize;
        }
        catch (Exception e) {
            throw new NullPointerException();
        }
    }

    /**
     * Returns true if this set contains no items.
     */
    @Override
    public boolean isEmpty() {
        return size_ == 0;
    }

    /**
     * Returns the number of items in this set.
     */
    @Override
    public int size() {
        return size_;
    }
    /**
     * Returns an ArrayList containing all the items in this set, in sorted order.
     */
    @Override
    public ArrayList<T> toArrayList() {
        ArrayList<T> result = new ArrayList<>();
        Stack<Node> stack = new Stack<>();
        Node ptr = root_;

        while (!stack.isEmpty() || ptr != null) {
            while (ptr != null) {
                stack.add(ptr);
                ptr = ptr.left_;
            }
            ptr = stack.pop();
            result.add(ptr.value_);
            ptr = ptr.right_;
        }
        return result;
    }

    /**
     * Updates the size of current bst.
     * @param node the node that scanning start from
     * @return the updated size
     */
    public int updateSize(Node node) {
        if (node == null) {
            return 0;
        }
        size_ = updateSize(node.left_) + updateSize(node.right_) + 1;
        return size_;
    }

    /**
     * @return the root node of current bst
     */
    public Node getRoot() {
        return root_;
    }

    /**
     * Prints the bst in the pre-order.
     */
    public void printPreOrderedTree() {
        List<T> result = new ArrayList<>();
        Stack<Node> stack = new Stack<>();
        Node p = root_;
        while (! stack.isEmpty() || p != null) {
            while (p != null) {
                result.add(p.value_);
                System.out.print(p.value_ + " ");
                stack.add(p);
                p = p.left_;
            }
            p = stack.pop().right_;
        }
        System.out.println("");
    }

    /**
     * Compares two binary search trees for equality.
     * @param rhs the bst to be compared with this
     * @return true if two trees are both empty/identical
     */
    public boolean equals(BinarySearchTree<T> rhs) {
        if (root_ == rhs.root_) {
            return true;
        }
        if (root_ == null || rhs.root_ == null) {
            return false;
        }
        return root_.value_.equals(rhs.root_.value_) &&
                root_.left_.value_.equals(rhs.root_.left_.value_) &&
                root_.right_.value_.equals(rhs.root_.right_.value_);
    }
}

/**
 * A helper class to print the bst as a real "tree"
 * Reference: <a href="https://stackoverflow.com/questions/4965335/how-to-print-binary-tree-diagram-in-java">...</a>
 */
class BTreePrinter {
    public static <T extends Comparable<?>> void printNode(BinarySearchTree.Node root) {
        int maxLevel = BTreePrinter.maxLevel(root);

        printNodeInternal(Collections.singletonList(root), 1, maxLevel);
    }

    private static <T extends Comparable<?>> void printNodeInternal(List<BinarySearchTree.Node> nodes, int level, int maxLevel) {
        if (nodes.isEmpty() || BTreePrinter.isAllElementsNull(nodes))
            return;

        int floor = maxLevel - level;
        int endgeLines = (int) Math.pow(2, (Math.max(floor - 1, 0)));
        int firstSpaces = (int) Math.pow(2, (floor)) - 1;
        int betweenSpaces = (int) Math.pow(2, (floor + 1)) - 1;

        BTreePrinter.printWhitespaces(firstSpaces);

        List<BinarySearchTree.Node> newNodes = new ArrayList<>();
        for (BinarySearchTree.Node node : nodes) {
            if (node != null) {
                System.out.print(node.value_);
                newNodes.add(node.left_);
                newNodes.add(node.right_);
            }
            else {
                newNodes.add(null);
                newNodes.add(null);
                System.out.print(" ");
            }

            BTreePrinter.printWhitespaces(betweenSpaces);
        }
        System.out.println("");

        for (int i = 1; i <= endgeLines; i++) {
            for (int j = 0; j < nodes.size(); j++) {
                BTreePrinter.printWhitespaces(firstSpaces - i);
                if (nodes.get(j) == null) {
                    BTreePrinter.printWhitespaces(endgeLines + endgeLines + i + 1);
                    continue;
                }

                if (nodes.get(j).left_ != null) {
                    System.out.print("/");
                }
                else {
                    BTreePrinter.printWhitespaces(1);
                }

                BTreePrinter.printWhitespaces(i + i - 1);

                if (nodes.get(j).right_ != null) {
                    System.out.print("\\");
                }
                else {
                    BTreePrinter.printWhitespaces(1);
                }

                BTreePrinter.printWhitespaces(endgeLines + endgeLines - i);
            }

            System.out.println("");
        }

        printNodeInternal(newNodes, level + 1, maxLevel);
    }

    private static void printWhitespaces(int count) {
        for (int i = 0; i < count; i++)
            System.out.print(" ");
    }

    private static <T extends Comparable<?>> int maxLevel(BinarySearchTree.Node node) {
        if (node == null)
            return 0;

        return Math.max(BTreePrinter.maxLevel(node.left_), BTreePrinter.maxLevel(node.right_)) + 1;
    }

    private static <T> boolean isAllElementsNull(List<T> list) {
        for (Object object : list) {
            if (object != null)
                return false;
        }

        return true;
    }
}