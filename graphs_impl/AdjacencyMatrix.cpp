#include "stdafx.h"
#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix(int32_t matrixSizeToSet)
{
	matrixSize = matrixSizeToSet;
	// init our matrix as a 2D-Array with a default 0 value
	matrix = new float*[matrixSize] {0};
	for (int32_t i = 0; i < matrixSize; i++)
	{
		matrix[i] = new float[matrixSize] {0};
	}		 
}

AdjacencyMatrix::~AdjacencyMatrix()
{

}

void AdjacencyMatrix::addDirectedEdge(int32_t from, int32_t to, float weight)
{	
	if (from < matrixSize && to < matrixSize)
	{
		matrix[from][to] = weight;
	}	
}

void AdjacencyMatrix::addUndirectedEdge(int32_t from, int32_t to, float weight)
{
	matrix[from][to] = weight;
	// because of it is an undirected edge we need to set the same weight for the reversed direction
	matrix[to][from] = weight;
}

std::vector<int32_t> AdjacencyMatrix::getAdjacencyList(int32_t sourceIndex)
{		
	std::vector<int32_t> adjacencyList;
	if (sourceIndex < getMatrixSize())
	{
		for (int32_t i = 0; i < matrixSize; ++i)
		{
			if (matrix[sourceIndex][i] != 0.f)
			{
				std::string debugString;

				debugString.append(std::to_string(matrix[sourceIndex][i]));
				adjacencyList.push_back(i);
			}

		}
	}
	
	return adjacencyList;
}
