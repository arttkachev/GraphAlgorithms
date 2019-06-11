// puzzle_game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Puzzle.h"


int main()
{
	// create a start state for the game
	std::string startGameState = Puzzle::generateRandomSolvableState();

	// vector that contains all states leading to the solution
	std::vector<std::string> path = Puzzle::breadthFirstSearch(startGameState);
	std::cout << "If you want to leave the program, write q and press Enter " << std::endl;
	std::cout << Puzzle::currentAlgorithm << " needs to visit " << path.size() << " states to find the win state" << std::endl;

	while (true)
	{
		for (std::string state : path)
		{
			Puzzle::printState(state);
		}						
		std::string q;		
		std::cin >> q;
		if (q == "q")
		{
			return 0;
		}
	}	    
}

