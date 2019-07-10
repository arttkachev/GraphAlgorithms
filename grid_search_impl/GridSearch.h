#pragma once
#include "Grid.h"
#include <map>
#include <stack>
#include <queue>

class GridSearch
{
public:
	GridSearch();
	~GridSearch();

	static std::vector<Grid::Point> depthFirstSearch(Grid& grid, Grid::Point& startPos, Grid::Point& endPos);
	static std::vector<Grid::Point> breadthFirstSearch(Grid& grid, Grid::Point& startPos, Grid::Point& endPos);
	static std::vector<Grid::Point> dijkstra(Grid& grid, Grid::Point& startPos, Grid::Point& endPos);

private:

	static std::vector<Grid::Point> generatePath(std::map<Grid::Point, Grid::Point> parentMap, Grid::Point & startState, Grid::Point& endState);
	static Grid::Point getClosestVertex(std::vector<Grid::Point> vectorOfPoints, std::map<Grid::Point, float> distanceMap);
};

