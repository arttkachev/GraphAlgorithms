#include "stdafx.h"
#include <windows.h>
#include "Grid.h"


Grid::Grid(int32_t _width, int32_t _height)
{
	width = _width;
	height = _height;

	// set a 2D-array
	grid = std::vector<std::vector<int32_t>>(_width, std::vector<int32_t>(_height, 1));
	points = std::vector<std::vector<Grid::Point>>(_width, std::vector<Grid::Point>(_height, Grid::Point(_width, _height)));
}


Grid::~Grid()
{
	
}

void Grid::setGridValues(int32_t atWidth, int32_t atHeight, int32_t value)
{	
	grid[atWidth][atHeight] = value;
}

float Grid::getCostOfEnteringCell(Point& cell)
{
	return (float)grid[(int32_t)cell.getX()][(int32_t)cell.getY()];
}

std::vector<Grid::Point> Grid::getAdjacentCells(int32_t x, int32_t y)
{
	std::vector<Grid::Point> adjacentCells;

	if (x > 0)
	{		
		if (points[x - 1][y].getvisualRepresentation() != untraversable)
		{
			adjacentCells.push_back(Grid::Point(x - 1, y));
		}		
	}

	if (x < width - 1)
	{
		if (points[x + 1][y].getvisualRepresentation() != untraversable)
		{
			adjacentCells.push_back(Grid::Point(x + 1, y));
		}		
	}

	if (y > 0)
	{
		if (points[x][y - 1].getvisualRepresentation() != untraversable)
		{
			adjacentCells.push_back(Grid::Point(x, y - 1));
		}		
	}

	if (y < height - 1)
	{
		if (points[x][y + 1].getvisualRepresentation() != untraversable)
		{
			adjacentCells.push_back(Grid::Point(x, y + 1));
		}		
	}

	return adjacentCells;
}

std::vector<Grid::Point> Grid::getAdjacentCells(Point & cell)
{
	return getAdjacentCells(cell.getX(), cell.getY());
}

void Grid::setStartPosition(Grid::Point startPos)
{
	points[startPos.getX()][startPos.getY()].setvisualRepresentation(start);	
}

void Grid::setEndPosition(Grid::Point endPos)
{
	points[endPos.getX()][endPos.getY()].setvisualRepresentation(end);	
}

void Grid::setObstacle(Grid::Point obstaclePosition)
{
	points[obstaclePosition.getX()][obstaclePosition.getY()].setvisualRepresentation(obstacle);
}

void Grid::setUntraversable(Grid::Point untraversablePosition)
{
	points[untraversablePosition.getX()][untraversablePosition.getY()].setvisualRepresentation(untraversable);
}

void Grid::MoveTo(Grid::Point pointToMove)
{
	points[pointToMove.getX()][pointToMove.getY()].setvisualRepresentation(moveTo);
}

void Grid::printGridState()
{	
	
	for (int32_t i = 0; i < width; i++)
	{			
		if (i != 0)
		{
			std::cout << std::endl;			
		}		
		
		for (int32_t j = 0; j < height; j++)
		{				
			std::cout << points[i][j].getvisualRepresentation();			
		}	
	}
}

void Grid::resetGridState()
{
	for (int32_t i = 0; i < width; i++)
	{
		if (i != 0)
		{
			std::cout << std::endl;
		}

		for (int32_t j = 0; j < height; j++)
		{
			points[i][j].setvisualRepresentation(traversable);
		}
	}
}

Grid::Point::Point(int32_t x_value, int32_t y_value)
{
	this->x = x_value;
	this->y = y_value;
	setvisualRepresentation("0");
}
