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
	
	// make a queue to hold and check neighbours	
	auto queue = new std::queue<Vertex<T>*>();
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

				// remove first element
				queue->push(neighbour);
			}
		}
		// and set
		firstVertexInQueue->setVertexVisited(true);
	}
	
}

template<typename T>
std::vector<Vertex<T>*>* SearchAlgorithms<T>::breadthFirstSearchWithGoal(Graph<T>* graph, Vertex<T>* sourceVertex, Vertex<T>* goalVertex)
{
	if (sourceVertex == goalVertex)
	{
		return new std::vector<Vertex<T>*>* {sourceVertex};
	}
	for (Vertex<T>* vertex : graph->getVerticies())
	{
		vertex->setParentVertex(nullptr);
		vertex->setDistance(0);
		vertex->setVertexVisited(false);
	}

	// make a queue to hold and check neighbours 
	std::queue<Vertex<T>*> queue = new std::queue<Vertex<T>*>();
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

				// remove first element
				queue->push(neighbour);
			}
		}
		// and set
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
