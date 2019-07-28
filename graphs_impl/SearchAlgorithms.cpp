#include "stdafx.h"
#include "SearchAlgorithms.h"


template<typename T>
SearchAlgorithms<T>::SearchAlgorithms()
{

}

template<typename T>
SearchAlgorithms<T>::~SearchAlgorithms()
{

}

template<typename T>
void SearchAlgorithms<T>::breadthFirstSearch(Graph<T>* graph, Vertex<T>* sourceVertex)
{
	for (Vertex<T>* vertex : graph->getVerticies())
	{
		vertex->setParentVertex(nullptr);
		vertex->setDistance(0);
		vertex->setVertexVisited(false);
	}
	
	// make a queue to hold and check neighbours FIFO	
	std::queue<Vertex<T>*> queue;
	queue.push(sourceVertex);	

	while (queue.size() > 0)
	{
		Vertex<T>* firstVertexInQueue = queue.front();
		queue.pop();

		for (Vertex<T>* neighbour : graph->getAdjacentVertices(firstVertexInQueue))
		{
			if (!neighbour->isVertexVisited())
			{
				neighbour->setParentVertex(firstVertexInQueue);
				neighbour->setDistance(firstVertexInQueue->getDistance() + graph->getEdgeWeight(firstVertexInQueue, neighbour));
				neighbour->setVertexVisited(true);

				// insert neighbour as last element
				queue.push(neighbour);
			}
		}
		// and set firstVertexInQueue visited
		firstVertexInQueue->setVertexVisited(true);
	}
	
}

template<typename T>
std::vector<Vertex<T>*> SearchAlgorithms<T>::breadthFirstSearchWithGoal(Graph<T>* graph, Vertex<T>* sourceVertex, Vertex<T>* goalVertex)
{
	if (sourceVertex == goalVertex)
	{
		return std::vector<Vertex<T>*> {sourceVertex};
	}
	for (Vertex<T>* vertex : graph->getVerticies())
	{
		vertex->setParentVertex(nullptr);
		vertex->setDistance(0);
		vertex->setVertexVisited(false);
	}

	// make a queue to hold and check neighbours 
	std::queue<Vertex<T>*> queue;
	queue.push(sourceVertex);

	while (queue->size() > 0)
	{
		Vertex<T>* firstVertexInQueue = queue.front();
		queue.pop();

		for (Vertex<T>* neighbour : graph->getAdjacentVertices(firstVertexInQueue))
		{
			if (!neighbour->isVertexVisited())
			{
				neighbour->setParentVertex(firstVertexInQueue);
				neighbour->setDistance(firstVertexInQueue->getDistance() + graph->getEdgeWeight(firstVertexInQueue, neighbour));
				neighbour->setVertexVisited(true);

				if (neighbour == goalVertex)
				{
					return getPathToSource(neighbour);
				}

				// insert neighbour as last element
				queue.push(neighbour);
			}
		}
		// and set firstVertexInQueue visited
		firstVertexInQueue->setVertexVisited(true);
	}

	// no path to goal vertex exists
	return nullptr;
}

template<typename T>
std::vector<Vertex<T>*> SearchAlgorithms<T>::getPathToSource(Vertex<T>* from)
{
	std::vector<Vertex<T>*> path;	
	Vertex<T>* next = from;

	while (next != nullptr)
	{		
		path.push_back(next);
		next = next->getParentVertex();
	}
	
	return path;
}

template<typename T>
void SearchAlgorithms<T>::depthFirstSearch(Graph<T>* graph, Vertex<T>* sourceVertex, bool reverseNeighbours)
{
	for (Vertex<T>* vertex : graph->getVerticies())
	{
		vertex->setParentVertex(nullptr);
		vertex->setDistance(0);
		vertex->setVertexVisited(false);
	}

	// to track visited vertices we use a stack FILO
	std::stack<Vertex<T>*> stack;
	stack.push(sourceVertex);

	while (stack.size() > 0)
	{
		Vertex<T>* upperVertexInStack = stack.top();
		stack.pop();

		std::vector<Vertex<T>*> neighbours = graph->getAdjacentVertices(upperVertexInStack);
		if (reverseNeighbours)
		{
			std::reverse(neighbours.begin(), neighbours.end());
		}

		for (Vertex<T>* neighbour : neighbours)
		{
			if (!neighbour->isVertexVisited())
			{
				neighbour->setParentVertex(upperVertexInStack);
				neighbour->setDistance(upperVertexInStack->getDistance() + graph->getEdgeWeight(upperVertexInStack, neighbour));
				neighbour->setVertexVisited(true);

				stack.push(neighbour);
			}
		}
		upperVertexInStack->setVertexVisited(true);

	}
}

template<typename T>
std::vector<Vertex<T>*> SearchAlgorithms<T>::depthFirstSearchWithGoal(Graph<T>* graph, Vertex<T>* sourceVertex, Vertex<T>* goalVertex, bool reverseNeighbours)
{
	if (sourceVertex == goalVertex)
	{
		return std::vector<Vertex<T>*>{ sourceVertex };
	}

	for (Vertex<T>* vertex : graph->getVerticies())
	{
		vertex->setParentVertex(nullptr);
		vertex->setDistance(0);
		vertex->setVertexVisited(false);
	}

	// make a stack to hold and check neighbours 
	std::stack<Vertex<T>*> stack;
	stack.push(sourceVertex);

	while (stack.size() > 0)
	{
		//FILO
		Vertex<T>* upperVertexInStack = stack.top();
		stack.pop();

		std::vector<Vertex<T>*> neighbours = graph->getAdjacentVertices(upperVertexInStack);

		if (reverseNeighbours)
		{
			std::reverse(neighbours.begin(), neighbours.end());
		}

		for (Vertex<T>* neighbour : neighbours)
		{
			if (!neighbour->isVertexVisited())
			{
				neighbour->setParentVertex(upperVertexInStack);
				neighbour->setDistance(upperVertexInStack->getDistance() + graph->getEdgeWeight(upperVertexInStack, neighbour));
				neighbour->setVertexVisited(true);

				if (neighbour == goalVertex)
				{
					return getPathToSource(neighbour);
				}

				// insert neighbour on the top
				stack.push(neighbour);
			}
		}
		// and set upperVertexInStack visited
		upperVertexInStack->setVertexVisited(true);
	}

	// no path found
	return std::vector<Vertex<T>*>();
}

template<typename T>
void SearchAlgorithms<T>::Dijkstra(Graph<T>* graph, Vertex<T>* sourceVertex)
{
	// vector of all vertices in the grpah that the algorithm needs to explore
	std::vector<Vertex<T>*> unfinishedVertices;
	
	// explore vertices and add them to the unfinished vector
	for (Vertex<T>* vertex : graph->getVerticies())
	{
		vertex->setParentVertex(nullptr);
		vertex->setDistance(std::numeric_limits<float>::max()); // imitates the infinity distance to other vertices (like Dijkstra works)
		unfinishedVertices.push_back(vertex);
	}

	// in Dijkstra the distance to the source vertex is always set to min. Means 0
	sourceVertex->setDistance(0.f);

	// main loop of the algorithm (the same pattern like in BFS and DFS)
	// while all vertices are not explored Dijkstra searches for a shortest path
	while (unfinishedVertices.size() > 0)
	{
		// find the closest vertex
		Vertex<T>* closestVertex = getClosestVertex(unfinishedVertices);

		// and remove it from unfinishedVertices because now it is finished
		// to remove a specific element from vector, first we need to find its index or pass in an iterator
		auto closestVertex_iter = std::find(unfinishedVertices.begin(), unfinishedVertices.end(), closestVertex);

		if (closestVertex_iter != unfinishedVertices.end())
		{
			unfinishedVertices.erase(closestVertex_iter);
		}


		// find adjacentVertices of the closest vertex to explore weights to them to find the shortest one by the weights
		// this is the heart of Dijkstra where we update the actual path to get the shortest one
		for (Vertex<T>* adjVertex : graph->getAdjacentVertices(closestVertex))
		{
			if (adjVertex->getDistance() > closestVertex->getDistance() + graph->getEdgeWeight(closestVertex, adjVertex))
			{
				// if true it means the algorithm found the shortest path. We update the distance of the current adjacent Vertex
				adjVertex->setDistance(closestVertex->getDistance() + graph->getEdgeWeight(closestVertex, adjVertex));

				// and we store closestVertex as the parent of found adjacent vertex to form the actual path
				adjVertex->setParent(closestVertex);
			}
		}
	}
}

template<typename T>
std::vector<Vertex<T>*> SearchAlgorithms<T>::DijkstraWithGoal(Graph<T>* graph, Vertex<T>* sourceVertex, Vertex<T>* goalVertex)

{
	// just check if the algorithm has found the goal
	if (sourceVertex == goalVertex)
	{		
		return std::vector<Vertex<T>*> { sourceVertex };
	}

	// vector of all vertices in the grpah that the algorithm needs to explore
	std::vector<Vertex<T>*> unfinishedVertices;

	// explore vertices and add them to the unfinished vector
	for (Vertex<T>* vertex : graph->getVerticies())
	{		
		vertex->setParentVertex(nullptr);
		vertex->setDistance(std::numeric_limits<float>::max()); // imitates the infinity distance to other vertices (like Dijkstra works)
		unfinishedVertices.push_back(vertex);
	}

	// in Dijkstra the distance to the source vertex is always set to min. Means 0
	sourceVertex->setDistance(0.f);

	// main loop of the algorithm (the same pattern like in BFS and DFS)
	// while all vertices are not explored Dijkstra searches for a shortest path
	while (unfinishedVertices.size() > 0)
	{
		// find the closest vertex		
		Vertex<T>* closestVertex = getClosestVertex(unfinishedVertices);

		// and remove it from unfinishedVertices because now it is finished
		// to remove a specific element from vector, first we need to find its index or pass in an iterator
		auto closestVertex_iter = std::find(unfinishedVertices.begin(), unfinishedVertices.end(), closestVertex);

		if (closestVertex_iter != unfinishedVertices.end())
		{			
			unfinishedVertices.erase(closestVertex_iter);
		}	

		// find again if the the closest vertex is a goal. 
		// If so, since we have removed it from unfinishedVertices, so, we know we have already updated all the shortest paths to it
		// and just return the path to the closest vertex because the shortest path has already been found
		if (closestVertex == goalVertex)
		{			
			return getPathToSource(closestVertex);
		}
		

		// otherwise, just continue as before

		// find adjacentVertices of the closest vertex to explore weights to them to find the shortest one by the weights
		// this is the heart of Dijkstra where we update the actual path to get the shortest one
		for (Vertex<T>* adjVertex : graph->getAdjacentVertices(closestVertex))
		{
			if (adjVertex->getDistance() > closestVertex->getDistance() + graph->getEdgeWeight(closestVertex, adjVertex))
			{
				// if true it means the algorithm found the shortest path. We update the distance of the current adjacent Vertex
				adjVertex->setDistance(closestVertex->getDistance() + graph->getEdgeWeight(closestVertex, adjVertex));

				// and we store closestVertex as the parent of found adjacent vertex to form the actual path
				adjVertex->setParentVertex(closestVertex);
			}
		}
	}
	
	return std::vector<Vertex<T>*>(); // no path found


}

template<typename T>
Vertex<T>* SearchAlgorithms<T>::getClosestVertex(std::vector<Vertex<T>*> verticesVector)
{
	Vertex<T>* closestVertex = verticesVector[0];

	for (Vertex<T>* vertex : verticesVector)
	{
		if (vertex->getDistance() < closestVertex->getDistance())
		{			
			closestVertex = vertex;
		}
	}
	return closestVertex;
}
