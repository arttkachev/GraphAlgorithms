// puzzle_game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <chrono>
#include <thread>
#include <Windows.h>
#include "Puzzle.h"


int main()
{	
	while (true)
	{
		// create a start state for the game
		std::string startGameState = Puzzle::generateRandomSolvableState();
		std::vector<std::string> path;

		std::cout << "Please, type what algorithm to use to solve the puzzle:" << std::endl;

		std::string algorithm;
		std::cin >> algorithm;

		if (algorithm == "dfs")
		{			
			// vector that contains all states leading to the solution
			path = Puzzle::depthFirstSearch(startGameState);
			std::reverse(path.begin(), path.end());
		}

		if (algorithm == "bfs")
		{
			// vector that contains all states leading to the solution
			path = Puzzle::breadthFirstSearch(startGameState);
			std::reverse(path.begin(), path.end());
		}

		if (algorithm == "q")
		{
			return 0;
		}
		
		for (std::string state : path)		
		{
			system("cls");
			Puzzle::printState(state);
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}

		std::cout << Puzzle::currentAlgorithm << " needs to visit " << path.size() << " states to find the WIN STATE" << std::endl;
		std::cout << "continue? " << std::endl;

		std::string continuation;
		std::cin >> continuation;

		if (continuation == "y")
		{			
			system("cls");
			continue;
		}

		else
		{
			return 0;
		}
	}	    
}

