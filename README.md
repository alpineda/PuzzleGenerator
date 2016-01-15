# PuzzleGenerator
A Puzzle Generator that uses a local-solver algorithm to 'find' the most challenging and fun puzzles within 60 seconds. This project was completed as a part of CSCI 360 "Introduction to Artificial Intelligence" at the University of Southern California instructed by Sven Koenig.

Project Objective:
Use local search methods (such as hill-climbing and simulated annealing) to generate puzzles that are optomized to be challenging and entertaining. Initially provided code has functionality for generating and evaluating puzzles (with respect to a predefined value function detailed below). The local-solver will be evaluated based on the value of the best puzzle it can generate within 60 seconds and will be tested using a variety of different puzzle constraints (i.e. size/complexity).

The Puzzle:
Each puzzle that is generated consists of a grid with r rows and c columns of cells. Each cell contains exactly one integer in the range from i to j (inclusive), where i and j are positive integers. The player of the puzzle has to start in the upper-left cell (start cell) and move with the smallest number of actions tothe lower-right cell (goal cell). If the player is in a cell that contains integer x, then they can perform one of at most four actions, namely either move x cells to the left (L), x cells to the right (R), x cells up (U), or x cells down (D), provided that they do not leave the grid. An example puzzle of size 5x5 is given below:

---------------------
| 3 | 2 | 1 | 4 | 1 |
---------------------
| 3 | 2 | 1 | 3 | 3 |
---------------------
| 3 | 3 | 2 | 1 | 4 |
---------------------
| 3 | 1 | 2 | 3 | 3 |
---------------------
| 1 | 4 | 4 | 3 | G |
---------------------

The shortest solution for the instance above is 19 moves: R D L R U D R L R L U D L D R R U D D
