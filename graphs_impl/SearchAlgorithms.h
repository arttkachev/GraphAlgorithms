#pragma once
#include <queue>
#include <stack>
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
	// BFS
	static void breadthFirstSearch(Graph<T>* graph, Vertex<T>* sourceVertex);
	static std::vector<Vertex<T>*>* breadthFirstSearchWithGoal(Graph<T>* graph, Vertex<T>* sourceVertex, Vertex<T>* goalVertex);
	static std::vector<Vertex<T>*>* getPathToSource(Vertex<T>* from);

	//DFS
	static void depthFirstSearch(Graph<T>* graph, Vertex<T>* sourceVertex, bool reverseNeighbours = false);
	static std::vector<Vertex<T>*>* depthFirstSearchWithGoal(Graph<T>* graph, Vertex<T>* sourceVertex, Vertex<T>* goalVertex, bool reverseNeighbours = false);

};

#include "SearchAlgorithms.cpp"


