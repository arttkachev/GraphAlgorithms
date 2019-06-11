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
	//std::cout << std::string(2, '\n');	
	std::cout << Puzzle::currentAlgorithm << " needs to visit " << path.size() << " states to find the WIN STATE" << std::endl;
	std::cout << "Write 'start' and press Enter to run the algorithm " << std::endl;
	std::cout << "Or if you want to leave the program, write 'q' and press Enter " << std::endl;

	while (true)
	{
		std::string command;
		std::cin >> command;
		if (command == "start")
		{
			for (std::string state : path)
			{
				Puzzle::printState(state);
			}
		}
		else
		{
			if (command == "q")
			{
				return 0;
			}
			else
			{
				command.clear();
			}
		}		
	}	    
}

