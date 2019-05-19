#include "stdafx.h"
#include "Vertex.h"

template<typename T>
Vertex<T>::Vertex(T dataToPass)
{
	data = dataToPass;	
}

template<class T>
Vertex<T>::~Vertex()
{

}

template<typename T>
void Vertex<T>::setIndex(int32_t indexToSet)
{	
	index = indexToSet;		
}

template<typename T>
void Vertex<T>::setParentVertex(Vertex<T>* parentVertexToSet)
{
	parent = parentVertexToSet;
}

template<typename T>
void Vertex<T>::setVertexVisited(bool isVertexVisited)
{
	isVisited = isVertexVisited;
}

template<typename T>
void Vertex<T>::setDistance(float distanceToSet)
{
	distance = distanceToSet;
}




