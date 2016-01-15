/** Code Written By Alexander Cordova - 2015 **/

#include "PuzzleGenerator.h"
using namespace std;

PuzzleGenerator::PuzzleGenerator(int _nRows, int _nColumns, int _minVal, int _maxVal)
	:nRows(_nRows), nColumns(_nColumns), minVal(_minVal), maxVal(_maxVal)
{}

Puzzle PuzzleGenerator::GeneratePuzzle()
{
	timer.StartTimer();
	maxtime = 58.0; // to make sure we don't exceed a minute

	// Declare variables for Simulated Annealing Algorithm
	double startingTemp;
	double alpha;
	double epsilon;

	// Determine if puzzle is "large" or not (so we can adjust how the algorithm performs)
	if (nRows*nColumns >= 80 || nRows*nColumns*(maxVal - minVal - 1) > 500)
	{
		startingTemp = 100;
		alpha = 0.9999;
		epsilon = 0.001;
	}
	else 
	{
		startingTemp = 100;
		alpha = 0.999;
		epsilon = 0.001;
	}


	Puzzle startingPuzzle(nRows, nColumns, minVal, maxVal);

	Puzzle bestPuzzle = SimulatedAnnealing_Exp(startingPuzzle, startingTemp, alpha, epsilon);
	int i = 0;

	while (timer.GetElapsedTime() < maxtime)
	{
		startingPuzzle = Puzzle(nRows, nColumns, minVal, maxVal);
		Puzzle p = SimulatedAnnealing_Exp(startingPuzzle, startingTemp, alpha, epsilon);
		if (p.GetValue() > bestPuzzle.GetValue())
		{
			bestPuzzle = p;
		}
		i++;
	}

	return bestPuzzle;

}


/** NOT USED (Simulated Annealing is Superior) **/
Puzzle PuzzleGenerator::RandomWalk(double timelimit)
{
	// A very simple function that start at a random configuration and keeps randomly modifying it
	// until it hits the time limit. Returns the best solution found so far.

	Puzzle p(nRows, nColumns, minVal, maxVal);	// Generate a random puzzle with the specified values.
	
	// Keep track of the best puzzle found so far (and its value).
	Puzzle bestPuzzle = p;			
	int bestValue = p.GetValue();
	
	// Keep track of the time so we don't exceed it.
	Timer t;
	t.StartTimer();
	
	// Loop until we hit the time limit.
	while (t.GetElapsedTime() < timelimit-0.1)	// To make sure that we don't exceed the time limit, we stop just before we hit the time limit.
	{
		// Generate a successor of p by randomly changing the value of a random cell 
		// (since we are doing a random walk, we just replace p with its successor).
		p = p.GetRandomSuccessor();	
		
		// Update the current best solution.
		if (p.GetValue() > bestValue)	// Calling GetValue() for the first time is costly
										// since the puzzle has to be evaluated first.
		{
			bestValue = p.GetValue();	// Calling it a second time simply returns the value that was computed before.
			bestPuzzle = p;
		}
	}
	
	return bestPuzzle;
	
	// The following code is not executed in this function. It exists just as an example for getting all the successors of a puzzle.
	vector<Puzzle> successors;
	bestPuzzle.GetAllSuccessors(successors);
}


/** NOT USED (Simulated Annealing is Superior) **/
Puzzle PuzzleGenerator::HillClimbing(double timelimit, Puzzle p)
{
	// Function that uses hillclimbing algorithm to find best value puzzle.
	// Returns best puzzle found after timelimit or local max when if it is found before time limit

	Puzzle bestPuzzle = p;

	// Keep track of the time so we don't exceed it.
	Timer t;
	t.StartTimer();

	while (t.GetElapsedTime() < timelimit-0.1)
	{
		// Generate all successors of bestPuzzle
		vector<Puzzle> successors;
		bestPuzzle.GetAllSuccessors(successors);

		Puzzle bestSuccessor = successors[0];

		// Determine highest valued successor and save as new best puzzle
		for (vector<Puzzle>::size_type i = 0; i != successors.size(); i++)
		{
			if (successors[i].GetValue() > bestSuccessor.GetValue())
			{
				bestSuccessor = successors[i];
			}
		}

		// Make sure that best successor is better than its parent (bestPuzzle), save it as the new best puzzle, and loop.
		if (bestSuccessor.GetValue() > bestPuzzle.GetValue())
		{
			bestPuzzle = bestSuccessor;
		}
		else 
		{
			// If it's not better, we found a local maximum. Save it and
			return bestPuzzle;
		}
	}

	printf("time limit reached\n");
	return bestPuzzle;
}


/** 
* 	Function that uses simulated annealing algorithm to find best value puzzle.
* 	TEMP_START = initial temperature
* 	ALPHA = how much the temperature is 'cooled' each iteration
* 	EPSILON = when temperature reaches the epsilon we're done
* 	returns the best puzzle found  
**/
Puzzle PuzzleGenerator::SimulatedAnnealing_Exp(Puzzle p, double temp_start, double alpha, double epsilon)
{

	Puzzle current = p;

	// Keep track of the time so we don't exceed it.
	Timer t;
	t.StartTimer();
	
	int i = 0; // iteration counter (for debugging)
	double temperature = temp_start;

	while (temperature > epsilon)
	{
		// get random successor
		Puzzle successor = current.GetRandomSuccessor();

		// if successor is a "good" move accept it
		if (successor.GetValue() > current.GetValue())
		{
			current = successor;
		}
		else // otherwise accept the move with probability of e^(deltaE/temperature)
		{
			int deltaE = successor.GetValue() - current.GetValue(); // calculate delta E
			double randVal = (rand() % 1000) / 1000.0; // generate random value between (0,1)
			double thresh = exp(deltaE/temperature);
			if (randVal < thresh)
			{
				//printf("successor value randomly ACCEPTED\n");
				current = successor;
			}
		}
		

		// cool temperature each iteration
		temperature *= alpha;

		// increment iteration counter
		i++;

	}
	
	return current;
}


Puzzle PuzzleGenerator::SimulatedAnnealing_Linear(Puzzle p, double temp_start, double delta, double epsilon)
{
	// Function that uses simulated annealing algorithm to find best value puzzle.
	// TEMP_START = initial temperature
	// DELTA = amount that temperature decreases per iteration
	// returns the best puzzle found 

	Puzzle current = p;

	// Keep track of the time so we don't exceed it.
	Timer t;
	t.StartTimer();
	
	int i = 0; // iteration counter (for debugging)
	double temperature = temp_start;

	while (temperature > epsilon)
	{
		//printf ("\nSIMULATED ANNEALING ITERATION %i\n", i);


		// get random successor
		Puzzle successor = current.GetRandomSuccessor();
		//printf ("current value = %i\n", current.GetValue());
		//printf ("successor value = %i\n", successor.GetValue());
		//printf ("temperature = %f\n", temperature);

		// if successor is a "good" move accept it
		if (successor.GetValue() > current.GetValue())
		{
			//printf("successor value > current value...ACCEPTED!\n");
			current = successor;
		}
		else // otherwise accept the move with probability of e^(deltaE/temperature)
		{
			int deltaE = successor.GetValue() - current.GetValue(); // calculate delta E
			//printf("deltaE = %i\n", deltaE);
			double randVal = (rand() % 1000) / 1000.0; // generate random value between (0,1)
			//printf("randVal = %f\n", randVal);
			double thresh = exp(deltaE/temperature);
			//printf("thresh = %f\n", thresh);
			if (randVal < thresh)
			{
				//printf("successor value randomly ACCEPTED\n");
				current = successor;
			}
		}
		

		// cool temperature each iteration
		temperature -= delta;

		// increment iteration counter
		i++;

	}
	
	return current;
}


