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
	std::queue<Vertex<T>*> *queue = new std::queue<Vertex<T>*>();
	queue->push(sourceVertex);	

	while (queue->size() > 0)
	{
		Vertex<T>* firstVertexInQueue = queue->front();
		queue->pop();

		for (Vertex<T>* neighbour : graph->getAdjacentVertices(firstVertexInQueue))
		{
			if (!neighbour->isVertexVisited())
			{
				neighbour->setParentVertex(firstVertexInQueue);
				neighbour->setDistance(firstVertexInQueue->getDistance() + graph->getEdgeWeight(firstVertexInQueue, neighbour));
				neighbour->setVertexVisited(true);

				// insert neighbour as last element
				queue->push(neighbour);
			}
		}
		// and set firstVertexInQueue visited
		firstVertexInQueue->setVertexVisited(true);
	}
	
}

template<typename T>
std::vector<Vertex<T>*>* SearchAlgorithms<T>::breadthFirstSearchWithGoal(Graph<T>* graph, Vertex<T>* sourceVertex, Vertex<T>* goalVertex)
{
	if (sourceVertex == goalVertex)
	{
		return new std::vector<Vertex<T>*> {sourceVertex};
	}
	for (Vertex<T>* vertex : graph->getVerticies())
	{
		vertex->setParentVertex(nullptr);
		vertex->setDistance(0);
		vertex->setVertexVisited(false);
	}

	// make a queue to hold and check neighbours 
	std::queue<Vertex<T>*> *queue = new std::queue<Vertex<T>*>();
	queue->push(sourceVertex);

	while (queue->size() > 0)
	{
		Vertex<T>* firstVertexInQueue = queue->front();
		queue->pop();

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
				queue->push(neighbour);
			}
		}
		// and set firstVertexInQueue visited
		firstVertexInQueue->setVertexVisited(true);
	}

	// no path to goal vertex exists
	return nullptr;
}

template<typename T>
std::vector<Vertex<T>*>* SearchAlgorithms<T>::getPathToSource(Vertex<T>* from)
{
	std::vector<Vertex<T>*> *path = new std::vector<Vertex<T>*>();	
	Vertex<T>* next = from;

	while (next != nullptr)
	{
		path->push_back(next);
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
	std::stack<Vertex<T>*> *stack = new std::stack<Vertex<T>*>();
	stack->push(sourceVertex);

	while (stack->size() > 0)
	{
		Vertex<T>* upperVertexInStack = stack->top();
		stack->pop();

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

				stack->push(neighbour);
			}
		}
		upperVertexInStack->setVertexVisited(true);

	}
}

template<typename T>
std::vector<Vertex<T>*>* SearchAlgorithms<T>::depthFirstSearchWithGoal(Graph<T>* graph, Vertex<T>* sourceVertex, Vertex<T>* goalVertex, bool reverseNeighbours)
{
	if (sourceVertex == goalVertex)
	{
		return new std::vector<Vertex<T>*>{ sourceVertex };
	}

	for (Vertex<T>* vertex : graph->getVerticies())
	{
		vertex->setParentVertex(nullptr);
		vertex->setDistance(0);
		vertex->setVertexVisited(false);
	}

	// make a stack to hold and check neighbours 
	std::stack<Vertex<T>*> *stack = new std::stack<Vertex<T>*>();
	stack->push(sourceVertex);

	while (stack->size() > 0)
	{
		//FILO
		Vertex<T>* upperVertexInStack = stack->top();
		stack->pop();

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
				stack->push(neighbour);
			}
		}
		// and set upperVertexInStack visited
		upperVertexInStack->setVertexVisited(true);
	}

	// no path found
	return nullptr;	
}
