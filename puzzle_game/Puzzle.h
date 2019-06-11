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

	// utility functions

	// used to get information about the current state is solvable or not
	// used inside the next method to initialize the initial state for the game that can be solved
	static bool isSolvable(std::string state);

	// used to initialize our initial state of the game
	static std::string generateRandomSolvableState();

	// just check if we have reached a win condition
	static bool isWinCondition(std::string state);

	// find a direction in which it is possible to move the *
	static std::vector<std::string> getNeighbourStates(std::string state);

	// find a path between to a win state 
	static std::vector<std::string> generatePath(std::map<std::string, std::string> parentMap, std::string endState);

	// debug 
	static std::string printState(std::string state);

	// search functions
	static std::vector<std::string> breadthFirstSearch(std::string initialState);
	static std::vector<std::string> depthFirstSearch(std::string initialState);



};

