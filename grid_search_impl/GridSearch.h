#pragma once
#include "Grid.h"
#include <map>
#include <stack>
#include <queue>
#include <functional>
#include "CustomPriorityQueue.h"

class GridSearch
{
public:
	GridSearch();
	~GridSearch();

	struct SearchResult
	{
		std::vector <Grid::Point> path;
		std::vector <Grid::Point> visited;
	};
	
	static std::vector<Grid::Point> depthFirstSearch(Grid& grid, Grid::Point& startPos, Grid::Point& endPos);
	static std::vector<Grid::Point> breadthFirstSearch(Grid& grid, Grid::Point& startPos, Grid::Point& endPos);
	static std::vector<Grid::Point> dijkstra(Grid& grid, Grid::Point& startPos, Grid::Point& endPos);
	static GridSearch::SearchResult bestFirstSearch(Grid& grid, Grid::Point& startPos, Grid::Point& endPos);

private:

	static std::vector<Grid::Point> generatePath(std::map<Grid::Point, Grid::Point> parentMap, Grid::Point & startState, Grid::Point& endState);
	static Grid::Point getClosestVertex(std::vector<Grid::Point> vectorOfPoints, std::map<Grid::Point, float> distanceMap);
	static float calculateManhattanHeuristic(Grid::Point a, Grid::Point b);
	static float calculateEuclideanHeuristic(Grid::Point a, Grid::Point b);
};

