#include "stdafx.h"
#include "GridSearch.h"


GridSearch::GridSearch()
{

}

GridSearch::~GridSearch()
{

}

GridSearch::SearchResult GridSearch::depthFirstSearch(Grid & grid, Grid::Point & startPos, Grid::Point & endPos)
{
	
	if (startPos == endPos)
	{		
		std::vector <Grid::Point> visitedPoints;
		visitedPoints.push_back(startPos);
		GridSearch::SearchResult searchResult;
		searchResult.path = visitedPoints;
		searchResult.visited = visitedPoints;
		return searchResult;
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
			if (!visitedMap.count(adj))
			{								
				visitedMap.insert(std::pair<Grid::Point, Grid::Point>(adj, node));
				stack.push(adj);
				
				if (adj == endPos)
				{
					//visitedMap.erase(adj);
					std::vector <Grid::Point> visitedPoints;
					for (std::map <Grid::Point, Grid::Point> ::iterator it = visitedMap.begin(); it != visitedMap.end(); it++)
					{
						visitedPoints.push_back(it->first);
					}
					GridSearch::SearchResult searchResult;
					searchResult.path = generatePath(visitedMap, startPos, adj);
					searchResult.visited = visitedPoints;

					return searchResult;
				}
			}
		}
		
		if (!visitedMap.count(node))
		{			
			visitedMap.insert(std::pair<Grid::Point, Grid::Point>(node, node));
		}

	}

	// no path found
	return SearchResult();
}

GridSearch::SearchResult GridSearch::breadthFirstSearch(Grid & grid, Grid::Point & startPos, Grid::Point & endPos)
{
	if (startPos == endPos)
	{
		std::vector <Grid::Point> visitedPoints;
		visitedPoints.push_back(startPos);
		GridSearch::SearchResult searchResult;
		searchResult.path = visitedPoints;
		searchResult.visited = visitedPoints;
		return searchResult;

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
					std::vector <Grid::Point> visitedPoints;
					for (std::map <Grid::Point, Grid::Point> ::iterator it = visitedMap.begin(); it != visitedMap.end(); it++)
					{
						visitedPoints.push_back(it->first);
					}
					GridSearch::SearchResult searchResult;
					searchResult.path = generatePath(visitedMap, startPos, adj);
					searchResult.visited = visitedPoints;

					return searchResult;
				}
			}
		}

		if (!visitedMap.count(node))
		{
			visitedMap.insert(std::pair<Grid::Point, Grid::Point>(node, node));
		}


	}
	// no path found
	return SearchResult();
}

GridSearch::SearchResult GridSearch::dijkstra(Grid & grid, Grid::Point & startPos, Grid::Point & endPos)
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
			std::vector <Grid::Point> visitedPoints;
			for (std::map <Grid::Point, Grid::Point> ::iterator it = visitedMap.begin(); it != visitedMap.end(); it++)
			{
				visitedPoints.push_back(it->first);
			}
			GridSearch::SearchResult searchResult;
			searchResult.path = generatePath(visitedMap, startPos, vertex);
			searchResult.visited = visitedPoints;

			return searchResult;

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
	return SearchResult();
}

GridSearch::SearchResult GridSearch::dijkstraWithPriorityMap(Grid & grid, Grid::Point & startPos, Grid::Point & endPos)
{
	std::priority_queue<Grid::Point, std::vector<Grid::Point>, std::greater<Grid::Point>> queue;	
	std::map<Grid::Point, float> distanceMap;
	std::map<Grid::Point, Grid::Point> visitedMap;	
	startPos.setPriority(0.f);
	queue.push(startPos);
	distanceMap.insert(std::pair<Grid::Point, float>(startPos, 0.f));
	visitedMap.insert(std::pair<Grid::Point, Grid::Point>(startPos, startPos));

	while (!queue.empty())
	{
		Grid::Point current = queue.top();
		queue.pop();

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
				adj.setPriority(newDist);
				queue.push(adj);
				

			}
		}
	}


	return SearchResult();
}

GridSearch::SearchResult GridSearch::bestFirstSearch(Grid & grid, Grid::Point & startPos, Grid::Point & endPos)
{
	std::priority_queue <Grid::Point, std::vector<Grid::Point>, std::greater<Grid::Point>> queue;	
	std::map<Grid::Point, float> distanceMap;
	std::map<Grid::Point, Grid::Point> visitedMap;

	startPos.setPriority(0.f);
	queue.push(startPos);

	distanceMap.insert(std::pair<Grid::Point, float>(startPos, 0.f));
	visitedMap.insert(std::pair<Grid::Point, Grid::Point>(startPos, startPos));

	while (!queue.empty())
	{
		Grid::Point current = queue.top();
		queue.pop();

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
				neighbour.setPriority(priority);
				queue.push(neighbour);
				
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

	std::priority_queue <Grid::Point, std::vector<Grid::Point>, std::greater<Grid::Point>> queue;	
	std::map<Grid::Point, float> distanceMap;
	std::map<Grid::Point, Grid::Point> visitedMap;

	startPos.setPriority(0.f);
	queue.push(startPos);
	
	distanceMap[startPos] = 0;
	visitedMap.insert(std::pair<Grid::Point, Grid::Point>(startPos, startPos));
	visitedMap.at(startPos) = startPos;
	
	while (!queue.empty())
	{
		Grid::Point current = queue.top();
		queue.pop();
		
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
				neighbour.setPriority(priority);
				queue.push(neighbour);				

				// set found lowest-cost neighbour as current vertex
				visitedMap.insert(std::pair<Grid::Point, Grid::Point>(neighbour, current));
				visitedMap.at(neighbour) = current;
			}
		}
	}

	// no path found
	return GridSearch::SearchResult();
}

GridSearch::SearchResult GridSearch::biDirectionalAStarSearch(Grid & grid, Grid::Point & startPos, Grid::Point & endPos)
{
	// true if opened from the start queue, false if opened by the end queue, not opened if not exists in the map
	std::map<Grid::Point, bool> openedBy;
	std::priority_queue <Grid::Point, std::vector<Grid::Point>, std::greater<Grid::Point>> startQueue;
	std::priority_queue <Grid::Point, std::vector<Grid::Point>, std::greater<Grid::Point>> endQueue;
	//CustomPriorityQueue startQueue;
	//CustomPriorityQueue endQueue;

	// the same code like in A* implementation
	std::map <Grid::Point, float> startDistanceMap;
	std::map <Grid::Point, Grid::Point> startVisitedMap;
	std::map <Grid::Point, float> endDistanceMap;
	std::map <Grid::Point, Grid::Point> endVisitedMap;

	// start the startQueue
	startPos.setPriority(0.f);
	startQueue.push(startPos);
	startDistanceMap[startPos] = 0;
	startVisitedMap.insert(std::pair<Grid::Point, Grid::Point>(startPos, startPos));
	// set parent of the startPos (null)
	startVisitedMap.at(startPos) = startPos;
	openedBy.insert(std::pair<Grid::Point, bool>(startPos, true));
	openedBy.at(startPos) = true;

	// start the endQueue
	endPos.setPriority(0.f);
	endQueue.push(endPos);
	endDistanceMap[endPos] = 0;
	endVisitedMap.insert(std::pair<Grid::Point, Grid::Point>(endPos, endPos));
	// set parent of the endPos (null)
	endVisitedMap.at(endPos) = endPos;
	openedBy.insert(std::pair<Grid::Point, bool>(endPos, false));
	openedBy.at(endPos) = false;
	

	// main loop
	while (!startQueue.empty() && !endQueue.empty())
	{		
		// from start
		Grid::Point current = startQueue.top();
		startQueue.pop();

		if (openedBy.count(current) && openedBy.at(current) == false)
		{
			
			// found goal or the frontier from the endQueue
			// return solution
			std::vector<Grid::Point> startPath = generatePath(startVisitedMap, startPos, current); // generate path from the start to the gaol
			std::vector<Grid::Point> endPath = generatePath(endVisitedMap, endPos, current); // generate path from the goal to the start (bi-directional)
			
			std::vector<Grid::Point> allPath = std::vector<Grid::Point>(startPath);
			// append the path from the end to get all paths
			allPath.insert(std::end(allPath), std::begin(endPath), std::end(endPath));

			std::vector<Grid::Point> allVisited;
			for (std::map <Grid::Point, Grid::Point> ::iterator it = startVisitedMap.begin(); it != startVisitedMap.end(); it++)
			{
				allVisited.push_back(it->first);
			}

			for (std::map <Grid::Point, Grid::Point> ::iterator it = endVisitedMap.begin(); it != endVisitedMap.end(); it++)
			{
				allVisited.push_back(it->first);
			}
			GridSearch::SearchResult searchResult;
			searchResult.path = allPath;
			searchResult.visited = allVisited;

			return searchResult;
		}

		for (Grid::Point neighbour : grid.getAdjacentCells(current))
		{
			float newCost = startDistanceMap[current] + grid.getCostOfEnteringCell(neighbour);
			if (!startDistanceMap.count(neighbour) || newCost < startDistanceMap[neighbour])
			{
				startDistanceMap[neighbour] = newCost;
				openedBy[neighbour] = true;

				// calculate F(n) = G(n) + H(n) - steps from startPos + steps to (from) endPos (heuristics)
				// the goal of the algorithm to keep F(n) as lowest as possible because F(n) is how our path is long
				float priority = newCost + calculateManhattanHeuristic(endPos, neighbour);

				// send this neighbour with calculated priority to our priority_map
				neighbour.setPriority(priority);
				startQueue.push(neighbour);

				// set found lowest-cost neighbour as current vertex
				startVisitedMap.insert(std::pair<Grid::Point, Grid::Point>(neighbour, current));
				startVisitedMap.at(neighbour) = current;
			}
		}

		// from end
		current = endQueue.top();
		endQueue.pop();

		if (openedBy.count(current) && openedBy.at(current) == true)
		{
			// found goal or the frontier from the startQueue
			// return solution
			std::vector<Grid::Point> startPath = generatePath(startVisitedMap, startPos, current); // generate path from the start to the gaol
			std::vector<Grid::Point> endPath = generatePath(endVisitedMap, endPos, current); // generate path from the goal to the start (bi-directional)

			std::vector<Grid::Point> allPath = std::vector<Grid::Point>(startPath);
			// append the path from the end to get all paths
			allPath.insert(std::end(allPath), std::begin(endPath), std::end(endPath));

			std::vector<Grid::Point> allVisited;
			for (std::map <Grid::Point, Grid::Point> ::iterator it = startVisitedMap.begin(); it != startVisitedMap.end(); it++)
			{
				allVisited.push_back(it->first);
			}

			for (std::map <Grid::Point, Grid::Point> ::iterator it = endVisitedMap.begin(); it != endVisitedMap.end(); it++)
			{
				allVisited.push_back(it->first);
			}
			GridSearch::SearchResult searchResult;
			searchResult.path = allPath;
			searchResult.visited = allVisited;

			return searchResult;
		}

		for (Grid::Point neighbour : grid.getAdjacentCells(current))
		{
			float newCost = endDistanceMap[current] + grid.getCostOfEnteringCell(neighbour);
			if (!endDistanceMap.count(neighbour) || newCost < endDistanceMap[neighbour])
			{
				endDistanceMap[neighbour] = newCost;
				openedBy[neighbour] = false;

				// calculate F(n) = G(n) + H(n) - steps from startPos + steps to (from) endPos (heuristics)
				// the goal of the algorithm to keep F(n) as lowest as possible because F(n) is how our path is long
				float priority = newCost + calculateManhattanHeuristic(startPos, neighbour);

				// send this neighbour with calculated priority to our priority_map
				neighbour.setPriority(priority);
				endQueue.push(neighbour);

				// set found lowest-cost neighbour as current vertex
				endVisitedMap.insert(std::pair<Grid::Point, Grid::Point>(neighbour, current));
				endVisitedMap.at(neighbour) = current;
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
