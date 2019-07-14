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

GridSearch::SearchResult GridSearch::dijkstraWithPriorityMap(Grid & grid, Grid::Point & startPos, Grid::Point & endPos)
{
	CustomPriorityQueue queue;
	std::map<Grid::Point, float> distanceMap;
	std::map<Grid::Point, Grid::Point> visitedMap;
	queue.enqueue(startPos, 0);
	distanceMap.insert(std::pair<Grid::Point, float>(startPos, 0.f));
	visitedMap.insert(std::pair<Grid::Point, Grid::Point>(startPos, startPos));

	while (!queue.isEmpty())
	{
		Grid::Point current = queue.dequeue();
		if (current == endPos)
		{
			std::vector <Grid::Point> visitedPoints;
			for (std::map <Grid::Point, Grid::Point> ::iterator it = visitedMap.begin(); it != visitedMap.end(); it++)
			{
				visitedPoints.push_back(it->first);
			}
			GridSearch::SearchResult searchResult;
			searchResult.path = generatePath(visitedMap, startPos, current);
			searchResult.visited = visitedPoints;

			return searchResult;

		}

		for (Grid::Point adj : grid.getAdjacentCells(current))
		{
			float newDist = distanceMap[current] + grid.getCostOfEnteringCell(adj);
			if (!distanceMap.count(adj) || newDist < distanceMap[adj])
			{
				distanceMap[adj] = newDist;
				visitedMap.insert(std::pair<Grid::Point, Grid::Point>(adj, current));
				visitedMap.at(adj) = current;
				queue.enqueue(adj, newDist);

			}
		}
	}


	return SearchResult();
}

GridSearch::SearchResult GridSearch::bestFirstSearch(Grid & grid, Grid::Point & startPos, Grid::Point & endPos)
{
	//std::priority_queue <Grid::Point, std::vector<Grid::Point>, std::greater<Grid::Point>> queue;
	CustomPriorityQueue queue;
	std::map<Grid::Point, float> distanceMap;
	std::map<Grid::Point, Grid::Point> visitedMap;

	//startPos.setPriority(0);
	queue.enqueue(startPos, 0);
	distanceMap.insert(std::pair<Grid::Point, float>(startPos, 0.f));
	visitedMap.insert(std::pair<Grid::Point, Grid::Point>(startPos, startPos));

	while (!queue.isEmpty())
	{
		Grid::Point current = queue.dequeue();
		//queue.pop();

		if (current == endPos)
		{
			std::vector <Grid::Point> visitedPoints;
			for (std::map <Grid::Point, Grid::Point> ::iterator it = visitedMap.begin(); it != visitedMap.end(); it++)
			{
				visitedPoints.push_back(it->first);
			}
			GridSearch::SearchResult searchResult;
			searchResult.path = generatePath(visitedMap, startPos, current);
			searchResult.visited = visitedPoints;

			return searchResult;

		}

		for (Grid::Point neighbour : grid.getAdjacentCells(current))
		{
			if (!visitedMap.count(neighbour))
			{
				float priority = calculateManhattanHeuristic(endPos, neighbour);
				//neighbour.setPriority(priority);
				queue.enqueue(neighbour, priority);
				visitedMap.insert(std::pair<Grid::Point, Grid::Point>(neighbour, current));
				distanceMap.insert(std::pair<Grid::Point, float>(neighbour, distanceMap[current] + grid.getCostOfEnteringCell(neighbour)));
			}
		}
	}
	// no path found
	return SearchResult();
}

GridSearch::SearchResult GridSearch::aStarSearch(Grid & grid, Grid::Point & startPos, Grid::Point & endPos)
{
	// with priority_map the algorithms is always takes more promising vertices with lowest total path cost
	// this is a whole idea of the A* search
	CustomPriorityQueue queue;
	std::map<Grid::Point, float> distanceMap;
	std::map<Grid::Point, Grid::Point> visitedMap;
	queue.enqueue(startPos, 0);
	distanceMap[startPos] = 0;
	visitedMap.insert(std::pair<Grid::Point, Grid::Point>(startPos, startPos));
	visitedMap.at(startPos) = startPos;
	
	while (!queue.isEmpty())
	{
		Grid::Point current = queue.dequeue();
		if (current == endPos)
		{
			std::vector <Grid::Point> visitedPoints;
			for (std::map <Grid::Point, Grid::Point> ::iterator it = visitedMap.begin(); it != visitedMap.end(); it++)
			{
				visitedPoints.push_back(it->first);
			}
			GridSearch::SearchResult searchResult;
			searchResult.path = generatePath(visitedMap, startPos, current);
			searchResult.visited = visitedPoints;

			return searchResult;
		}

		for (Grid::Point neighbour : grid.getAdjacentCells(current))
		{
			// calculate G(n) - steps from startPos
			float newCost = distanceMap[current] + grid.getCostOfEnteringCell(neighbour);
			if (!distanceMap.count(neighbour) || newCost < distanceMap[neighbour])
			{
				// set found lowest-cost value to neighbour in distance map. In other words, it updates our shortest path
				distanceMap[neighbour] = newCost;

				// calculate F(n) = G(n) + H(n) - steps from startPos + steps to (from) endPos (heuristics)
				// the goal of the algorithm to keep F(n) as lowest as possible because F(n) is how our path is long
				float priority = newCost + calculateManhattanHeuristic(endPos, neighbour);

				// send this neighbour with calculated priority to our priority_map
				queue.enqueue(neighbour, priority);

				// set found lowest-cost neighbour as current vertex
				visitedMap.insert(std::pair<Grid::Point, Grid::Point>(neighbour, current));
				visitedMap.at(neighbour) = current;
			}
		}
	}

	// no path found
	return GridSearch::SearchResult();
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

float GridSearch::calculateManhattanHeuristic(Grid::Point a, Grid::Point b)
{
	return (float)std::abs(a.getX() - b.getX()) + std::abs(a.getY() - b.getY());
}

float GridSearch::calculateEuclideanHeuristic(Grid::Point a, Grid::Point b)
{
	return (float)std::sqrt((a.getX() - b.getX()) * (a.getX() - b.getX()) + (a.getY() - b.getY()) * (a.getY() - b.getY()));
}
