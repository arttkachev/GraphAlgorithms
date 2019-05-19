#pragma once
#include <vector>
#include <string>
#include <iostream>

/*
  we implement the Graph with the AdjacencyMatrix
  note, there is a method called getAdjacencyList, but actually it returns a vector An AdjacencyList term is being used for consistency of AI terms
*/
class AdjacencyMatrix
{
public:
	// ctr takes in the size of the matrix. Matrix is intended to be squared
	AdjacencyMatrix(int32_t matrixSizeToSet);
	~AdjacencyMatrix();

	// public interface to communicate with this class
	inline int32_t getMatrixSize() const
	{
		return matrixSize;
	}

	inline float getEdgeWeight(int32_t from, int32_t to) const
	{
		// just returns data (values) passed in vertices that we set before
		return matrix[from][to];
	}

	void addDirectedEdge(int32_t from, int32_t to, float weight);
	void addUndirectedEdge(int32_t from, int32_t to, float weight);	
	std::vector<int32_t>getAdjacencyList(int32_t sourceIndex);
	

private:
	/*
	we use a 2D array for our matrix. C++ is not very good for multidiamentional arrays of unknown sizes, so, it would be better to use
	a vector of vectors but for training purposes I'm gonna use an array of pointers to arrays
	*/
	float** matrix = nullptr;	
	//float** matrix = nullptr;
	int32_t matrixSize;
};

