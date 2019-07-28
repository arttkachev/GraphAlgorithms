// grid_search_impl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "Grid.h"
#include "GridSearch.h"


int main()
{	
	while (true)
	{	
		// create grid
		Grid grid(90, 50);

		// set start & end positions on the grid
		Grid::Point startPos(89, 0);
		Grid::Point endPos(0, 49);

		grid.setStartPosition(startPos);
		grid.setEndPosition(endPos);

		// set obstacles on the grid USED FOR TESTING DFS/BFS/DIJKSTRA
		for (int32_t i = 0; i < grid.getWidth(); i++)
		{
			for (int32_t j = 0; j < grid.getHeight(); j++)
			{
				//if (i > 35)
				//{
					//grid.setObstacle(Grid::Point(i, j));
					//grid.setGridValues(i, j, 100);


				//}
			}
		}

		std::cout << "Please, type what Search Algorithm you would like to test:" << std::endl;

		GridSearch::SearchResult searchResult;
		std::string algorithmToUse;
		std::cin >> algorithmToUse;

		if (algorithmToUse == "dfs")
		{
			searchResult = GridSearch::depthFirstSearch(grid, startPos, endPos);
			std::reverse(searchResult.path.begin(), searchResult.path.end());
		}

		if (algorithmToUse == "bfs")
		{
			searchResult = GridSearch::breadthFirstSearch(grid, startPos, endPos);
			std::reverse(searchResult.path.begin(), searchResult.path.end());
		}

		if (algorithmToUse == "dijkstra")
		{
			searchResult = GridSearch::dijkstraWithPriorityMap(grid, startPos, endPos);
			std::reverse(searchResult.path.begin(), searchResult.path.end());
		}

		if (algorithmToUse == "a*")
		{
			searchResult = GridSearch::aStarSearch(grid, startPos, endPos);
			std::reverse(searchResult.path.begin(), searchResult.path.end());
		}

		if (algorithmToUse == "bidirectional_a*")
		{
			searchResult = GridSearch::biDirectionalAStarSearch(grid, startPos, endPos);
			std::reverse(searchResult.path.begin(), searchResult.path.end());
		}

		if (algorithmToUse == "best_first_search")
		{
			searchResult = GridSearch::bestFirstSearch(grid, startPos, endPos);
			std::reverse(searchResult.path.begin(), searchResult.path.end());
		}

		if (algorithmToUse == "q")
		{
			return 0;
		}
		
		system("cls");
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
				cPos.X = searchResult.path[i].getX();
				cPos.Y = searchResult.path[i].getY();

				hCon = GetStdHandle(STD_OUTPUT_HANDLE);

				SetConsoleCursorPosition(hCon, cPos);
				std::cout << "-";
				Sleep(40);



				//grid.printGridState();
				//Sleep(200);
				//system("cls");
			}			
		}		

		system("cls");
		grid.printGridState();
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "Number of visited nodes : " << searchResult.visited.size() << std::endl;
		std::cout << "Continue?" << std::endl;

		std::string continuation;
		std::cin >> continuation;

		if (continuation == "y")
		{
			grid.resetGridState();
			system("cls");
			continue;
		}

		else
		{
			return 0;
		}		
	}	
	
}

