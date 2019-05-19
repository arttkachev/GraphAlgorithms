// graphs_impl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Vertex.h"
#include "Graph.h"
#include "AdjacencyMatrix.h"

int main()
{	
	// let's check our graph
	// create new vertices	
	Vertex<std::string> * v1 = new Vertex<std::string>("v1");
	Vertex<std::string> * v2 = new Vertex<std::string>("v2");
	Vertex<std::string> * v3 = new Vertex<std::string>("v3");
	Vertex<std::string> * v4 = new Vertex<std::string>("v4");
	Vertex<std::string> * v5 = new Vertex<std::string>("v5");

	// create a vector that contains all vertices
	std::vector<Vertex<std::string>*> vertices = { v1, v2, v3, v4, v5 };	

	// construct the graph
	Graph<std::string> graph(vertices);	
		
	// create edges between different vertices
	graph.createDirectedEdge(v1, v2, 3);	
	graph.createDirectedEdge(v2, v3, 4);
	graph.createDirectedEdge(v2, v4, 5);
	graph.createDirectedEdge(v4, v1, 1);
	graph.createDirectedEdge(v4, v5, 34);

	// print out debug to check the graph is built correctly
	std::cout << graph.outputDebug();	
	
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

