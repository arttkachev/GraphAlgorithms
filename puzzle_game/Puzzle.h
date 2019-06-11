#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <random>

// in graph vertices we will store states of our puzzle
class Puzzle
{
public:
	Puzzle();
	~Puzzle();

	// data member storing the algorithm in use
	static std::string currentAlgorithm;

	// utility functions

	// checks if the passed in state can be solved or not
	// used inside the next method to initialize the initial state for the game that can be solved
	static bool isSolvable(std::string state);

	// generates our initial random state to start the game
	static std::string generateRandomSolvableState();

	// just checks if the algorithm has reached a win condition
	static bool isWinCondition(std::string state);

	// find next state (direction) in which it is possible to move the *
	static std::vector<std::string> getNeighbourStates(std::string state);

	// returns a path from a start state to a win state
	// contains all states which were visited
	static std::vector<std::string> generatePath(std::map<std::string, std::string> parentMap, std::string endState);

	// debug 
	static std::string printState(std::string state);

	// search functions
	static std::vector<std::string> breadthFirstSearch(std::string initialState);
	static std::vector<std::string> depthFirstSearch(std::string initialState);

};

