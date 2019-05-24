#include "stdafx.h"
#include "Graph.h"

template<typename T>
Graph<T>::Graph(std::vector<Vertex<T>*> verticesToConstruct)
{	
	// vector that will store all vertices
	vertices = verticesToConstruct;
	int32_t counter = 0;

	// set the index to each vertex	
	for (std::vector<Vertex<T>*>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
	{	
		(*it)->setIndex(counter);
		counter++;		
	}

	// construct a new AdjacencyMatrix to represent our Graph
	adjacencyMatrix = new AdjacencyMatrix(counter);
}

template<typename T>
Graph<T>::~Graph()
{
	delete adjacencyMatrix;
	adjacencyMatrix = nullptr;
}

template<typename T>
std::vector<Vertex<T>*> Graph<T>::getVerticies()
{
	return vertices;
}

template<typename T>
void Graph<T>::createDirectedEdge(int32_t fromIndex, int32_t toIndex, float weight)
{	
	adjacencyMatrix->addDirectedEdge(fromIndex, toIndex, weight);
}

template<typename T>
void Graph<T>::createDirectedEdge(Vertex<T>* fromVertex, Vertex<T>* toVertex, float weight)
{	
	this->createDirectedEdge(fromVertex->getIndex(), toVertex->getIndex(), weight);
}

template<typename T>
void Graph<T>::createUndirectedEdge(int32_t fromIndex, int32_t toIndex, float weight)
{
	adjacencyMatrix->addUndirectedEdge(fromIndex, toIndex, weight);
}

template<typename T>
void Graph<T>::createUndirectedEdge(Vertex<T>* fromVertex, Vertex<T>* toVertex, float weight)
{
	this->createUndirectedEdge(fromVertex->getIndex(), toVertex->getIndex(), weight);
}

template<typename T>
std::vector<Vertex<T>*> Graph<T>::getAdjacentVertices(int32_t sourceIndex)
{	
	std::vector<int32_t> adjacentIndices = adjacencyMatrix->getAdjacencyList(sourceIndex);
	std::vector<Vertex<T>*> adjacentVertices;
	int32_t index = 0;
	for (std::vector<int32_t>::const_iterator it = adjacentIndices.begin(); it != adjacentIndices.end(); it++)
	{
		adjacentVertices.push_back(vertices[adjacentIndices[index]]);
		index++;
	}	
	return adjacentVertices;
}

template<typename T>
std::vector<Vertex<T>*> Graph<T>::getAdjacentVertices(Vertex<T>* sourceVertex)
{	
	return this->getAdjacentVertices(sourceVertex->getIndex());
}

template<typename T>
float Graph<T>::getEdgeWeight(Vertex<T>* vertex1, Vertex<T>* vertex2)
{
	return adjacencyMatrix->getEdgeWeight(vertex1->getIndex(), vertex2->getIndex());
}

template<typename T>
std::string Graph<T>::outputDebug()
{
	std::string debugString;
	debugString.append("Simple Weighted Graph Implemented With C++:");
	debugString.append(std::string(3, '\n'));
	for (std::vector<Vertex<T>*>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
	{
		debugString.append((*it)->getData());		
		std::vector<Vertex<T>*> adjacentVertices = getAdjacentVertices(*it);		
		if (adjacentVertices.size() > 0)
		{
			for (std::vector<Vertex<T>*>::const_iterator adj_it = adjacentVertices.begin(); adj_it != adjacentVertices.end(); adj_it++)
			{
				debugString.append("\n");
				debugString.append("Has edge to: ");
				debugString.append((*adj_it)->getData());
				debugString.append(" with weight = ");
				debugString.append(std::to_string(getEdgeWeight((*it), (*adj_it))));
			}
		}
		else
		{
			debugString.append("\n");
			debugString.append("No outgoing edges");
		}
		debugString.append(std::string(3, '\n'));
	}
	return debugString;
}
		
	
