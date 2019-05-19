#pragma once
#include <string>

// class template that represents a node in the graph
template <typename T>
class Vertex
{
public:	
	Vertex(T dataToPass);
	~Vertex();

	// public interface to communicate with this class	
	inline T getData() const
	{
		return data;
	}

	inline int32_t getIndex() const
	{
		return index;
	}

	inline Vertex<T>* getParentVertex() const
	{
		return parent;
	}

	inline bool isVertexVisited() const
	{
		return isVisited;
	}

	inline float getDistance() const
	{
		return distance;
	}

	void setIndex(int32_t indexToSet);
	void setParentVertex(Vertex<T>* parentVertexToSet);
	void setVertexVisited(bool isVertexVisited);
	void setDistance(float distanceToSet);

private:
	// generic type variable that holds the data of the vertex
	T data;
	// index of the vertex. By the index, we refer to the specific vertex
	int32_t index = 0;

	// data to keep track of search in the Graph
	Vertex<T>* parent = nullptr;
	bool isVisited = false;
	float distance = 0.f;
};

#include "Vertex.cpp"



