/** Code Written by Alexander Cordova - 2015 **/

#include <stdio.h>
#include <stdlib.h>
#include <climits>
#include <math.h>
#include <algorithm>
#include "Puzzle.h"
#include "Timer.h"

class PuzzleGenerator{


public:
	PuzzleGenerator(int nRows, int nColumns, int minVal, int maxVal);
	Puzzle GeneratePuzzle(); 
	Puzzle RandomWalk(double timelimit);
	Puzzle HillClimbing(double timelimit, Puzzle p);
	Puzzle SimulatedAnnealing_Exp(Puzzle p, double temp_start, double alpha, double epsilon);
	Puzzle SimulatedAnnealing_Linear(Puzzle p, double temp_start, double delta, double epsilon);
	

private:
	int nRows, nColumns, minVal, maxVal;
	Timer timer;
	double maxtime;

};



