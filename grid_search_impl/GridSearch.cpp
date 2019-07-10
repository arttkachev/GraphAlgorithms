#include "stdafx.h"
#include "GridSearch.h"


GridSearch::GridSearch()
{
}


GridSearch::~GridSearch()
{
}

std::vector<Grid::Point> GridSearch::depthFirstSearch(Grid & grid, Grid::Point & startPos, Grid::Point & endPos)
{
	
	if (startPos == endPos)
	{		
		return std::vector<Grid::Point> { startPos };
	}
	
	
	std::map<Grid::Point, Grid::Point> visitedMap;
	std::stack<Grid::Point> stack;
	stack.push(startPos);
	
	while (stack.size() > 0)
	{
		
		Grid::Point node = stack.top();
		stack.pop();

		// searching for adjacent cells
		
		for (Grid::Point adj : grid.getAdjacentCells(node))
		{
			//std::cout << adj.getX() << "  " << adj.getY();
			//std::cout << std::endl;
			//std::cout << "adj";
			//std::cout << std::endl;
			
			if (!visitedMap.count(adj))
			{	
				//grid.MoveTo(adj);
				//std::cout << "NOT FOUND IN MAP! ADJ";
				//std::cout << std::endl;				
				visitedMap.insert(std::pair<Grid::Point, Grid::Point>(adj, node));
				stack.push(adj);
				
				if (adj == endPos)
				{
					//visitedMap.erase(adj);
					return generatePath(visitedMap, startPos, adj);
				}
			}
		}
		
		if (!visitedMap.count(node))
		{
			//std::cout << "NOT COUNT NODE ";
			//std::cout << std::endl;			
			
			visitedMap.insert(std::pair<Grid::Point, Grid::Point>(node, node));
		}
		
	}
	
	return std::vector<Grid::Point>();
}

std::vector<Grid::Point> GridSearch::breadthFirstSearch(Grid & grid, Grid::Point & startPos, Grid::Point & endPos)
{
	if (startPos == endPos)
	{
		return std::vector<Grid::Point> {startPos};
	}

	// keep track of visited vertices and parents for each vertex
	std::map<Grid::Point, Grid::Point> visitedMap;
	std::queue<Grid::Point> queue;
	queue.push(startPos);

	while (queue.size() > 0)
	{
		Grid::Point node = queue.front();
		queue.pop();

		// searching for neighbours (neighbour states)		
		for (Grid::Point adj : grid.getAdjacentCells(node))
		{
			if (!visitedMap.count(adj))
			{
				visitedMap.insert(std::pair<Grid::Point, Grid::Point>(adj, node));
				queue.push(adj);

				if (adj == endPos)
				{
					return generatePath(visitedMap, startPos, adj);
				}
			}
		}

		if (!visitedMap.count(node))
		{
			visitedMap.insert(std::pair<Grid::Point, Grid::Point>(node, node));
		}


	}
	// no solution found
	return std::vector<Grid::Point>();
}

std::vector<Grid::Point> GridSearch::dijkstra(Grid & grid, Grid::Point & startPos, Grid::Point & endPos)
{
	std::vector<Grid::Point> unfinishedVertices;
	std::map<Grid::Point, float> distanceMap;
	std::map<Grid::Point, Grid::Point> visitedMap;

	unfinishedVertices.push_back(startPos);

	distanceMap.insert(std::pair<Grid::Point, float> (startPos, 0.f));
	visitedMap.insert(std::pair<Grid::Point, Grid::Point> (startPos, startPos));

	while (unfinishedVertices.size() > 0)
	{
		// find the closest vertex	
		Grid::Point vertex = getClosestVertex(unfinishedVertices, distanceMap);
		
		// and remove it from unfinishedVertices because now it is finished
		// to remove a specific element from vector, first we need to find its index or pass in an iterator
		auto closestVertex_iter = std::find(unfinishedVertices.begin(), unfinishedVertices.end(), vertex);

		if (closestVertex_iter != unfinishedVertices.end())
		{
			unfinishedVertices.erase(closestVertex_iter);
		}

		if (vertex == endPos)
		{
			return generatePath(visitedMap, startPos, vertex);
		}

		for (Grid::Point adj : grid.getAdjacentCells(vertex))
		{
			if (!visitedMap.count(adj))
			{
				unfinishedVertices.push_back(adj);
			}

			float adjDist = distanceMap.count(adj) ? distanceMap[adj] : std::numeric_limits<float>::max();
			float vDist = distanceMap.count(vertex) ? distanceMap[vertex] : std::numeric_limits<float>::max();

			if (adjDist > vDist + grid.getCostOfEnteringCell(adj))
			{
				if (distanceMap.count(adj))
				{
					distanceMap[adj] = vDist + grid.getCostOfEnteringCell(adj);
				}

				else
				{
					distanceMap.insert(std::pair<Grid::Point, float>(adj, vDist + grid.getCostOfEnteringCell(adj)));
				}

				if (visitedMap.count(adj))
				{
					visitedMap.at(adj) = vertex;
				}

				else
				{
					visitedMap.insert(std::pair<Grid::Point, Grid::Point>(adj, vertex));
				}
			}
		}
	}

	// no path found
	return std::vector<Grid::Point>();
}


std::vector<Grid::Point> GridSearch::generatePath(std::map<Grid::Point, Grid::Point> parentMap, Grid::Point & startState, Grid::Point & endState)
{
	std::vector<Grid::Point> path;
	Grid::Point parent = endState;	

	while (parent != startState)	
	{			
		path.push_back(parent);
		parent = parentMap.at(parent);		
	}
	return path;
}

Grid::Point GridSearch::getClosestVertex(std::vector<Grid::Point> vectorOfPoints, std::map<Grid::Point, float> distanceMap)
{
	Grid::Point closestPoint = vectorOfPoints[0];

	for (Grid::Point vertex : vectorOfPoints)
	{
		if (distanceMap[vertex] < distanceMap[closestPoint])
		{
			closestPoint = vertex;
		}
	}
	return closestPoint;
}
