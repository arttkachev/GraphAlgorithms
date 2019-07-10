// grid_search_impl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Grid.h"
#include "GridSearch.h"


int main()
{
	// create grid
	Grid grid(17, 17);

	// set start & end positions on the grid
	Grid::Point startPos(16, 16);
	Grid::Point endPos(0, 16);

	grid.setStartPosition(startPos);
	grid.setEndPosition(endPos);

	// set obstacles on the grid
	
	for (int32_t i = 0; i < grid.getHeight(); i++)
	{
		for (int32_t j = 0; j < grid.getWidth(); j++)
		{
			if (j > 9 && i > 4 && i < 11)
			{
				grid.setObstacle(Grid::Point(i, j));
				grid.setGridValues(i, j, 100);
			}
		}
	}
	
	
	//std::vector<Grid::Point> path = GridSearch::depthFirstSearch(grid, startPos, endPos);
	//std::vector<Grid::Point> path = GridSearch::breadthFirstSearch(grid, startPos, endPos);
	std::vector<Grid::Point> path = GridSearch::dijkstra(grid, startPos, endPos);
	//std::cout << "test";	

	while ( true)
	{	
		
		for (int32_t i = 0; i < path.size(); i++)
		{
			if (path[i] != startPos && path[i] != endPos)
			{
				grid.MoveTo(path[i]);
			}
			//grid.MoveTo(path[i]);
		}
		
		
		grid.printGridState();
		std::cout << std::endl;
		std::string command;
		std::cin >> command;

		if (command == "q")
		{
			return 0;
		}		
	}    
}

