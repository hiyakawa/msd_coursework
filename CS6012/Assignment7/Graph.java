/*
 * Graph.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 7: PacMan!
 * File 1 of 3
 */

package assignment07;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.*;

public class Graph {
    class Node {
        private int xCoord_;
        private int yCoord_;
        private char value_;
        private boolean visited_;

        private Node(int xCoord, int yCoord, char value) {
            xCoord_ = xCoord;
            yCoord_ = yCoord;
            value_ = value;
            visited_ = false;
        }
    }

    private Node startNode_, goalNode_;
    ArrayList<Node> neighbours_ = new ArrayList<>();
    private Node[][] maze_;
    private int height_, width_;

    /**
     * Reads in a text file and parse it into a matrix of Node.
     * @param inputFile the path of input file
     */
    public void parseMaze(String inputFile) {
        File input = new File(inputFile);
        try {
            Scanner sc = new Scanner(input);

            try {
                String firstLine = sc.nextLine();
                String[] dimensions = firstLine.split(" ");
                height_ = Integer.parseInt(dimensions[0]);
                width_ = Integer.parseInt(dimensions[1]);
                maze_ = new Node[height_][width_];

                for (int row = 0; row < height_; row++) {
                    String curLine = sc.nextLine();

                    for (int col = 0; col < width_; col++) {
                        Node curNode = new Node(row, col, curLine.charAt(col));
                        maze_[row][col] = curNode;

                        // check if it's a start / goal node
                        switch (curNode.value_) {
                            case 'S' -> startNode_ = maze_[row][col];
                            case 'G' -> goalNode_ = maze_[row][col];
                        }
                    }
                }
            }
            catch (Exception e) {
                e.printStackTrace();
            }
        }
        catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    /**
     * Writes the solution into a text file using the given file path.
     * @param outputFile the path of output file
     */
    public void writeSolution(String outputFile) {
        File fileWriter = new File(outputFile);
        try (PrintWriter outPut = new PrintWriter(fileWriter)) {
            outPut.println(height_ + " " + width_);

            for (int i = 0; i < height_; i++) {
                for (int j = 0; j < width_; j++) {
                    Node curNode = maze_[i][j];
                    outPut.print(curNode.value_);
                }
                outPut.println();
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Returns all the neighbours of the input node who are start node / goal node or empty node.
     * @param curNode the given input node
     * @return all the neighbours of the input node who are start node / goal node or empty node
     */
    private ArrayList<Node> getNeighbours(Node curNode) {
        int curRow = curNode.xCoord_;
        int curCol = curNode.yCoord_;

        if (curNode.value_ != 'X') {
            Node upNeighbour = maze_[curRow - 1][curCol];
            Node downNeighbour = maze_[curRow + 1][curCol];
            Node leftNeighbour = maze_[curRow][curCol - 1];
            Node rightNeighbour = maze_[curRow][curCol + 1];

            ArrayList<Node> allNeighbours = new ArrayList<>() {{
                add(upNeighbour); add(downNeighbour); add(leftNeighbour); add(rightNeighbour);
            }};

            for (Node neighbour : allNeighbours) {
                // check if the neighbour is wall
                if (neighbour.value_ != 'X') {
                    neighbours_.add(neighbour);
                }
            }
        }

        return neighbours_;
    }

    /**
     * Implements breadth first search algorithm.
     */
    public void breadthFirstSearch() {
        HashMap<Node, Node> path = new HashMap<>();
        Queue<Node> queue = new LinkedList<>();

        startNode_.visited_ = true;
        queue.add(startNode_);

        while (! queue.isEmpty()) {
            // poll the first node
            Node curNode = queue.poll();

            if (curNode == goalNode_) {
                backTrackPath(curNode, path);
                return;
            }

            ArrayList<Node> curNeighbours = getNeighbours(curNode);

            for (Node curNeighbour : curNeighbours) {
                if (! curNeighbour.visited_) {
                    curNeighbour.visited_ = true;
                    queue.add(curNeighbour);
                    path.put(curNeighbour, curNode);
                }
            }
        }
    }

    /**
     * Keeps track of the path that we came from.
     * @param goalNode the goal node
     * @param path a hashmap that stores the path
     */
    private void backTrackPath(Node goalNode, HashMap<Node, Node> path) {
        if (goalNode == null) {
            return;
        }

        Node prevNode = path.get(goalNode);

        while (prevNode != startNode_) {
            prevNode.value_ = '.';
            prevNode = path.get(prevNode);
        }
    }

    /**
     * Prints the maze.
     */
    public void printMaze() {
        for (int i = 0; i < height_; i++) {
            for (int j = 0; j < width_; j++) {
                System.out.print(maze_[i][j].value_);
            }
            System.out.println();
        }
    }
}