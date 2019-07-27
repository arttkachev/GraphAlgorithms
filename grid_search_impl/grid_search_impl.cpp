// grid_search_impl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "Grid.h"
#include "GridSearch.h"


int main()
{
	// create grid
	Grid grid(50, 90);

	// set start & end positions on the grid
	Grid::Point startPos(0, 89);
	Grid::Point endPos(49, 0);

	grid.setStartPosition(startPos);
	grid.setEndPosition(endPos);

	// set obstacles on the grid USED FOR TESTING DFS/BFS/DIJKSTRA
	
	for (int32_t i = 0; i < grid.getHeight(); i++)
	{
		for (int32_t j = 0; j < grid.getWidth(); j++)
		{
			if (j > 9 && i > 4 && i < 11)
			{
				grid.setUntraversable(Grid::Point(i, j));
				grid.setGridValues(i, j, 100);
			}
		}
	}
	

	// set obstacles on the grid USED FOR TESTING BEST FIRST SEARCH
	/*
	for (int32_t i = 0; i < grid.getWidth(); i++)
	{
		for (int32_t j = 0; j < grid.getHeight(); j++)
		{	
			if (i <= 7 && i >= 3)
			{
				{
					if (j > 10)
					{
						grid.setGridValues(i, j, 200);
						grid.setObstacle(Grid::Point(i, j));
					}
				}
				
			}
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
		

	*/

	
	// algorithms to test

	GridSearch::SearchResult searchResult = GridSearch::depthFirstSearch(grid, startPos, endPos);
	//GridSearch::SearchResult searchResult = GridSearch::breadthFirstSearch(grid, startPos, endPos);
	//GridSearch::SearchResult searchResult = GridSearch::dijkstra(grid, startPos, endPos);
	//GridSearch::SearchResult searchResult = GridSearch::bestFirstSearch(grid, startPos, endPos);
	//GridSearch::SearchResult searchResult = GridSearch::aStarSearch(grid, startPos, endPos);
	//GridSearch::SearchResult searchResult = GridSearch::biDirectionalAStarSearch(grid, startPos, endPos);

	std::reverse(searchResult.path.begin(), searchResult.path.end());

	while (true)
	{
		
		grid.printGridState();

		for (uint32_t i = 0; i < searchResult.path.size(); i++)
		{
			if (searchResult.path[i] != startPos && searchResult.path[i] != endPos)
			{
				grid.MoveTo(searchResult.path[i]);



				HANDLE hCon;
				COORD cPos;
				hCon = GetStdHandle(STD_OUTPUT_HANDLE);
				std::cout.flush();
				cPos.Y = searchResult.path[i].getX();
				cPos.X = searchResult.path[i].getY();

				hCon = GetStdHandle(STD_OUTPUT_HANDLE);

				SetConsoleCursorPosition(hCon, cPos);
				std::cout << "-";
				Sleep(40);



				//grid.printGridState();
				//Sleep(200);
				//system("cls");
			}

			//}
			//grid.updateGridState();
			//Sleep(200);
			//system("cls");
			//grid.MoveTo(searchResult.path[i]);
		}


		
		//grid.printGridState();
		std::cout << std::endl;
		std::string command;
		std::cin >> command;

		if (command == "q")
		{
			return 0;
		}
	}
	
		
	
}

