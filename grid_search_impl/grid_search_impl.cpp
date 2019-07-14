// grid_search_impl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Grid.h"
#include "GridSearch.h"


int main()
{
	// create grid
	Grid grid(21, 21);

	// set start & end positions on the grid
	Grid::Point startPos(16, 10);
	Grid::Point endPos(4, 12);

	grid.setStartPosition(startPos);
	grid.setEndPosition(endPos);

	// set obstacles on the grid USED FOR TESTING DFS/BFS/DIJKSTRA
	/*
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
	*/

	// set obstacles on the grid USED FOR TESTING BEST FIRST SEARCH
	
	for (int32_t i = 0; i < grid.getWidth(); i++)
	{
		for (int32_t j = 0; j < grid.getHeight(); j++)
		{			
			if (i > 8 && i < 17)
			{
				if (i == 9 && j > 1 && j < 18)
				{
					grid.setUntraversable(Grid::Point(i, j));
					//grid.setGridValues(i, j, 200); SET WEIGHTS FOR DIJKSTRA
				}
				if (j == 2 || j == 17)
				{
					grid.setUntraversable(Grid::Point(i, j));
					//grid.setGridValues(i, j, 200); SET WEIGHTS FOR DIJKSTRA
				}
				
			}
		}
	}
		

	

	
	// algorithms to test

	//std::vector<Grid::Point> path = GridSearch::depthFirstSearch(grid, startPos, endPos);
	//std::vector<Grid::Point> path = GridSearch::breadthFirstSearch(grid, startPos, endPos);
	//std::vector<Grid::Point> path = GridSearch::dijkstra(grid, startPos, endPos);
	GridSearch::SearchResult searchResult = GridSearch::bestFirstSearch(grid, startPos, endPos);	

	while ( true)
	{	
		
		for (int32_t i = 0; i < searchResult.path.size(); i++)
		{
			if (searchResult.path[i] != startPos && searchResult.path[i] != endPos)
			{
				grid.MoveTo(searchResult.path[i]);
			}
			//grid.MoveTo(searchResult.path[i]);
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

