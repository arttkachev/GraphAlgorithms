#pragma once
#include <vector>
#include <iterator>
#include "Vertex.h"
#include "AdjacencyMatrix.h"

// class template that represents a graph
template <typename T>
class Graph
{
public:
	// ctr takes in the vector of pointers to all vertices	
	Graph(std::vector<Vertex<T>*> verticesToConstruct);
	~Graph();

	// public interface to communicate with this class
	std::vector<Vertex<T>*>getVerticies();
	void createDirectedEdge(int32_t fromIndex, int32_t toIndex, float weight = 1);
	void createDirectedEdge(Vertex<T>* fromVertex, Vertex<T>* toVertex, float weight = 1);
	void createUndirectedEdge(int32_t fromIndex, int32_t toIndex, float weight = 1);
	void createUndirectedEdge(Vertex<T>* fromVertex, Vertex<T>* toVertex, float weight = 1);
	std::vector<Vertex<T>*> getAdjacentVertices(int32_t sourceIndex);
	std::vector<Vertex<T>*> getAdjacentVertices(Vertex<T>* sourceVertex);
	float getEdgeWeight(Vertex<T>* vertex1, Vertex<T>* vertex2);
	std::string outputDebug();

private:
	std::vector<Vertex<T>*> vertices;
	AdjacencyMatrix* adjacencyMatrix;	
};

#include "Graph.cpp"