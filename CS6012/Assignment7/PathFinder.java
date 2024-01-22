/*
 * PathFinder.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 7: PacMan!
 * File 2 of 3
 */

package assignment07;

public class PathFinder {
    public static void solveMaze(String inputFile, String outputFile) {
        Graph maze = new Graph();
        maze.parseMaze(inputFile);
        maze.breadthFirstSearch();
        maze.writeSolution(outputFile);
    }
}
