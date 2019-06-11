#include "stdafx.h"
#include "Puzzle.h"


Puzzle::Puzzle()
{
}


Puzzle::~Puzzle()
{
}


bool Puzzle::isSolvable(std::string state)
{
	int32_t inversions = 0;

	// only works with 8 puzzle
	for (std::string::size_type i = 0; i < 9; i++)
	{
		if (state[i] == '*')
		{
			continue;
		}

		for (std::string::size_type j = i + 1; j < 9; j++)
		{
			if (state[j] == '*')
			{
				continue;
			}

			if (state[i] > state[j])
			{
				inversions++;
			}

		}

	}
	// if the number of inversions is even, then that state that passed in is solvable
	return inversions % 2 == 0;
}


std::string Puzzle::generateRandomSolvableState()
{	
	// only works with 8 puzzle
	const int32_t numOfValues = 9;
	// "12345678*"
	std::string state = "651342*87";

	// shuffle first time
	auto rng = std::default_random_engine{};
	//std::shuffle(&state[0], &state[numOfValues], rng);

	// shuffle initial state it to be not solved at start
	while (!isSolvable(state))
	{	
		//auto rng = std::default_random_engine{};
		std::shuffle(&state[0], &state[numOfValues], rng);		
	}
	return state;
}

bool Puzzle::isWinCondition(std::string state)
{
	return state == "12345678*";
}

std::vector<std::string> Puzzle::getNeighbourStates(std::string state)
{
	// string state 1234*5678
	// represents 1 2 3
	//            4 * 5
	//            6 7 8

	size_t emptyIndex = state.find("*");

	bool canMoveLeft = emptyIndex % 3 > 0;
	bool canMoveRight = emptyIndex % 3 < 2;
	bool canMoveUp = emptyIndex / 3 > 0;
	bool canMoveDown = emptyIndex / 3 < 2;

	std::vector<std::string> neighbours;

	if (canMoveLeft)
	{
		std::string newState(state);
		char newChar = newState[emptyIndex - 1]; // moving left Switch *
		newState[emptyIndex] = newChar;
		newState[emptyIndex - 1] = '*';
		neighbours.push_back(newState);
	}

	if (canMoveRight)
	{
		std::string newState(state);
		char newChar = newState[emptyIndex + 1]; // moving right. Switch *
		newState[emptyIndex] = newChar;
		newState[emptyIndex + 1] = '*';
		neighbours.push_back(newState);
	}

	if (canMoveUp)
	{
		std::string newState(state);
		char newChar = newState[emptyIndex - 3]; // moving up. Switch *
		newState[emptyIndex] = newChar;
		newState[emptyIndex - 3] = '*';
		neighbours.push_back(newState);
	}

	if (canMoveDown)
	{
		std::string newState(state);
		char newChar = newState[emptyIndex + 3]; // moving down. Switch *
		newState[emptyIndex] = newChar;
		newState[emptyIndex + 3] = '*';
		neighbours.push_back(newState);
	}
	return neighbours;
}

std::vector<std::string> Puzzle::generatePath(std::map<std::string, std::string> parentMap, std::string endState)
{
	std::vector<std::string> path;
	std::string parent = endState;
	while (parentMap.count(parent))
	{
		path.push_back(parent);
		parent = parentMap[parent];
	}
	return path;
}

std::string Puzzle::printState(std::string state)
{
	std::string printableState;
	printableState.append(state);
	std::cout << "Puzzle State:";
	std::cout << std::string(2, '\n');
	
	for (std::string::size_type i = 0; i < state.length(); i++)
	{		
		if (i % 3 == 2)
		{	
		
			std::cout << "  " << printableState[i];
			std::cout << std::string(2, '\n');
		}
		else
		{
			std::cout << "  " << printableState[i];
		}
		
		//printableState.append(state);
	}
	
	//std::cout << std::endl;
	return printableState;
}


std::vector<std::string> Puzzle::breadthFirstSearch(std::string initialState)
{
	if (isWinCondition(initialState))
	{
		return std::vector<std::string> {initialState};
	}

	// keep track of visited vertices and parents for each vertex
	std::map<std::string, std::string> visitedMap;
	std::queue<std::string> queue;
	queue.push(initialState);

	while (queue.size() > 0)
	{
		std::string node = queue.front();
		queue.pop();

		// searching for neighbours (neighbour states)
		
		for (std::string neighbour : getNeighbourStates(node))
		{
			if (!visitedMap.count(neighbour))
			{
				visitedMap.insert(std::pair<std::string, std::string>(neighbour, node));
				queue.push(neighbour);

				if (isWinCondition(neighbour))
				{
					return generatePath(visitedMap, neighbour);
				}
			}
		}
		
		if (!visitedMap.count(node))
		{			
			visitedMap.insert(std::pair<std::string, std::string>(node, ""));
		}
		
		
	}

	// no solution found
	return std::vector<std::string>();
}

std::vector<std::string> Puzzle::depthFirstSearch(std::string initialState)
{
	if (isWinCondition(initialState))
	{
		return std::vector<std::string> {initialState};
	}

	// keep track of visited vertices and parents for each vertex
	std::map<std::string, std::string> visitedMap;
	std::stack<std::string> stack;
	stack.push(initialState);
	

	while (stack.size() > 0)
	{
		std::string node = stack.top();
		stack.pop();		
		
		// searching for neighbours (neighbour states)
		for (std::string neighbour : getNeighbourStates(node))
		{
			
			if (!visitedMap.count(neighbour))
			{
				
				visitedMap.insert(std::pair<std::string, std::string>(neighbour, node));
				stack.push(neighbour);

				if (isWinCondition(neighbour))
				{
					return generatePath(visitedMap, neighbour);
				}
			}
		}
		if (!visitedMap.count(node))
		{
			visitedMap.insert(std::pair<std::string, std::string>(node, ""));
		}
	}

	// no solution found
	//std::cout << "no solution found" << std::endl;
	return std::vector<std::string>();;
}

