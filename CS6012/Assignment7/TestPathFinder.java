/*
 * TestPathFinder.java
 * Author: Muyuan Zhang
 * CS 6012 Assignment 7: PacMan!
 * File 3 of 3
 */

package assignment07;

import org.junit.jupiter.api.Test;

public class TestPathFinder {
    @Test
    void solveTinyMaze() {
        PathFinder.solveMaze("tinyMaze.txt", "tinyMazeOutput.txt");
    }

    @Test
    void solveBigMaze() {
        PathFinder.solveMaze("bigMaze.txt", "bigMazeOutput.txt");
    }

    @Test
    void solveClassicMaze() {
        PathFinder.solveMaze("classic.txt", "classicOutput.txt");
    }

    @Test
    void solveDemoMaze() {
        PathFinder.solveMaze("demoMaze.txt", "demoMazeOutput.txt");
    }

    @Test
    void solveMediumMaze() {
        PathFinder.solveMaze("mediumMaze.txt", "mediumMazeOutput.txt");
    }

    @Test
    void solveRandomMaze() {
        PathFinder.solveMaze("randomMaze.txt", "randomMazeOutput.txt");
    }

    @Test
    void solveStraightMaze() {
        PathFinder.solveMaze("straight.txt", "straightOutput.txt");
    }

    @Test
    void solveTinyOpenMaze() {
        PathFinder.solveMaze("tinyOpen.txt", "tinyOpenOutput.txt");
    }

    @Test
    void solveTurnMaze() {
        PathFinder.solveMaze("turn.txt", "turnOutput.txt");
    }

    @Test
    void unsolvableMaze() {
        PathFinder.solveMaze("unsolvable.txt", "unsolvableOutput.txt");
    }
}

