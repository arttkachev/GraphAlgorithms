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
	std::cout << path.size() << std::endl;
	

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
    return 0;
}

