#include "stdafx.h"
#include <windows.h>
#include "Grid.h"


Grid::Grid(int32_t _width, int32_t _height)
{
	width = _width;
	height = _height;

	// set a 2D-array
	grid = std::vector<std::vector<int32_t>>(_width, std::vector<int32_t>(_height, 1));
	cells = std::vector<std::vector<std::string>>(_width, std::vector<std::string>(_height, traversable));
	
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
		if (cells[x - 1][y] != untraversable)
		{
			adjacentCells.push_back(Grid::Point(x - 1, y));
		}
		
	}

	if (x < width - 1)
	{
		if (cells[x + 1][y] != untraversable)
		{
			adjacentCells.push_back(Grid::Point(x + 1, y));
		}
		
	}

	if (y > 0)
	{
		if (cells[x][y - 1] != untraversable)
		{
			adjacentCells.push_back(Grid::Point(x, y - 1));
		}
		
	}

	if (y < height - 1)
	{
		if (cells[x][y + 1] != untraversable)
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
	cells[startPos.getX()][startPos.getY()] = start;
	
}

void Grid::setEndPosition(Grid::Point endPos)
{
	cells[endPos.getX()][endPos.getY()] = end;
	
}

void Grid::setObstacle(Grid::Point obstaclePosition)
{
	cells[obstaclePosition.getX()][obstaclePosition.getY()] = obstacle;
}

void Grid::setUntraversable(Grid::Point untraversablePosition)
{
	cells[untraversablePosition.getX()][untraversablePosition.getY()] = untraversable;
}

void Grid::MoveTo(Grid::Point pointToMove)
{
	cells[pointToMove.getX()][pointToMove.getY()] = moveTo;
}

void Grid::removeCellFromGrid(int32_t atWidth, int32_t atHeight)
{
	//grid[atWidth].erase(atHeight);
}

void Grid::printGridState()
{	
	
	for (int32_t i = 0; i < width; i++)
	{	
		//std::cout << cells[i][0];
		
		if (i != 0)
		{
			std::cout << std::endl;			
		}
		
		
		for (int32_t j = 0; j < height; j++)
		{				
			std::cout << cells[i][j];
			//std::cout << " ";
		}	
				
	}
	
}

void Grid::updateGridState()
{
	HANDLE hCon;
	COORD cPos;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	
	//SetConsoleCursorPosition(hCon, cPos);
	static float test = 0;
	for (int32_t i = 0; i < width; i++)
	{
		cPos.Y =i ;
		if (i != 0)
		{
			
			//std::cout << std::endl;
			
			//SetConsoleCursorPosition(hCon, cPos);
			//std::cout << std::endl;
			//std::cout << moveTo;
		}
		
		for (int32_t j = 0; j < height; j++)
		{
			hCon = GetStdHandle(STD_OUTPUT_HANDLE);
			cPos.X = j ;
			
			//std::cout << j;
			SetConsoleCursorPosition(hCon, cPos);
			std::cout << "* ";
			
			
		}

	}
}

Grid::Point::Point(int32_t x_value, int32_t y_value)
{
	this->x = x_value;
	this->y = y_value;
}
