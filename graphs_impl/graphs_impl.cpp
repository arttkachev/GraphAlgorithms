// graphs_impl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Vertex.h"
#include "Graph.h"
#include "AdjacencyMatrix.h"
#include "SearchAlgorithms.h"

int main()
{	
	// let's check our graph
	// create new vertices	
	Vertex<std::string> * v1 = new Vertex<std::string>("v1");
	Vertex<std::string> * v2 = new Vertex<std::string>("v2");
	Vertex<std::string> * v3 = new Vertex<std::string>("v3");
	Vertex<std::string> * v4 = new Vertex<std::string>("v4");
	Vertex<std::string> * v5 = new Vertex<std::string>("v5");
	Vertex<std::string> * v6 = new Vertex<std::string>("v6");
	Vertex<std::string> * v7 = new Vertex<std::string>("v7");
	Vertex<std::string> * v8 = new Vertex<std::string>("v8");
	Vertex<std::string> * v9 = new Vertex<std::string>("v9");

	// create a vector that contains all vertices
	std::vector<Vertex<std::string>*> vertices = { v1, v2, v3, v4, v5, v6, v7, v8, v9 };	

	// construct the graph
	//Graph<std::string> graph(vertices);	
	Graph<std::string> *graph = new Graph<std::string>(vertices);
	
	
		
	// create edges between different vertices
	/*
	graph.createDirectedEdge(v1, v2, 3);	
	graph.createDirectedEdge(v2, v3, 4);
	graph.createDirectedEdge(v2, v4, 5);
	graph.createDirectedEdge(v4, v1, 1);
	graph.createDirectedEdge(v4, v5, 34);
	*/

	graph->createUndirectedEdge(v4, v5, 35);
	graph->createUndirectedEdge(v4, v2, 40);
	graph->createUndirectedEdge(v4, v1, 12);
	graph->createUndirectedEdge(v5, v6, 11);
	graph->createUndirectedEdge(v2, v5, 24);	
	graph->createUndirectedEdge(v2, v7, 44);
	graph->createUndirectedEdge(v2, v1, 31);	
	graph->createUndirectedEdge(v1, v3, 500);
	graph->createUndirectedEdge(v1, v7, 816);
	graph->createUndirectedEdge(v7, v6, 28);

	graph->createUndirectedEdge(v8, v9, 134);
	graph->createUndirectedEdge(v8, v1, 1);
	graph->createUndirectedEdge(v1, v3, 2);
	graph->createUndirectedEdge(v3, v9, 3);
	

	// print out debug to check the graph is built correctly
	std::cout << graph->outputDebug();
	
	// test BFS
	SearchAlgorithms<std::string>::breadthFirstSearch(graph, v3);	
	std::vector<Vertex<std::string>*> from_v7 = SearchAlgorithms<std::string>::getPathToSource(v7);

	std::cout << "Breadth First Search" << std::endl;
	std::cout << "The shortest path from v7" << std::endl;
	for (Vertex<std::string>* vertex : from_v7)
	{
		std::cout << vertex->getData() << std::endl;
	}
	
	// new line
	std::cout << std::endl;
	
	// test DFS
	SearchAlgorithms<std::string>::depthFirstSearch(graph, v4, true);
	std::vector<Vertex<std::string>*> from_v6 = SearchAlgorithms<std::string>::getPathToSource(v6);

	std::cout << "Depth First Search" << std::endl;
	std::cout << "The path from v6" << std::endl;
	for (Vertex<std::string>* vertex : from_v6)
	{
		std::cout << vertex->getData() << std::endl;
	}

	// new line
	std::cout << std::endl;

	// test DFS with Goal
	
	std::vector<Vertex<std::string>*> path = SearchAlgorithms<std::string>::depthFirstSearchWithGoal(graph, v6, v3, true);
	std::cout << "Depth First Search With Goal" << std::endl;
	std::cout << "The path from v3 to v6" << std::endl;
	for (Vertex<std::string>* vertex : path)
	{
		std::cout << vertex->getData() << std::endl;
	}

	// new line
	std::cout << std::endl;

	// test Dijkstra
	std::vector<Vertex<std::string>*> shortestPath = SearchAlgorithms<std::string>::DijkstraWithGoal(graph, v8, v9);	

	std::cout << "Dijkstra" << std::endl;
	std::cout << "The shortest path from v8 to v9" << std::endl;
	for (Vertex<std::string>* vertex : shortestPath)
	{
		std::cout << vertex->getData() << std::endl;
	}
	
	// program termination	
	while (true)
	{	
		std::string q;
		std::cout << "Please, type 'q' and press 'Enter' to exit" << std::endl;	
		std::cin >> q;
		if (q == "q")
		{
			return 0;
		}		
	}    
}

