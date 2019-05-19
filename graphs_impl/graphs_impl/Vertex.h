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

	void setIndex(int32_t indexToSet);

private:
	// generic type variable that holds the data of the vertex
	T data;
	// index of the vertex. By the index, we refer to the specific vertex
	int32_t index = 0;
};

#include "Vertex.cpp"



