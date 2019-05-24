#pragma once
#include <queue>
#include "Graph.h"
#include "Vertex.h"

// class template for SearchAlgorithms
template <typename T>
class SearchAlgorithms
{
public:
	SearchAlgorithms();
	~SearchAlgorithms();

	// public interface to communicate with this class
	static void breadthFirstSearch(Graph<T>* graph, Vertex<T>* sourceVertex);
	static std::vector<Vertex<T>*>* breadthFirstSearchWithGoal(Graph<T>* graph, Vertex<T>* sourceVertex, Vertex<T>* goalVertex);
	static std::vector<Vertex<T>*>* getPathToSource(Vertex<T>* from);

};

#include "SearchAlgorithms.cpp"


