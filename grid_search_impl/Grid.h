#pragma once
#include <vector>
#include <tuple>
#include <string>
#include <iostream>

class Grid
{	
public:

	class Point // this class is used to index into the grid
	{
	public:
		// ctr
		Point(int32_t x_value, int32_t y_value);

		int32_t x = 0;
		int32_t y = 0;

		int32_t priority = 0;

		inline int32_t getPriority() { return priority; }
		inline void setPriority(int32_t priorityToSet) { priority = priorityToSet; }

		std::string representation;

		inline int32_t getX() { return x; }
		inline int32_t getY() { return y; }

		inline std::string getRepresentation() { return representation; }
		inline void setRepresentation(std::string representationToSet) { representation = representationToSet; }

		inline void setX(int32_t x_value) { x = x_value; }
		inline void setY(int32_t y_value) { y = y_value; }

		// + operator overloading for this class
		inline bool operator == (const Grid::Point &rhs) const
		{
			return this->x == rhs.x && this->y == rhs.y;
		}

		inline bool operator != (const Grid::Point &rhs) const
		{
			return this->x != rhs.x || this->y != rhs.y;
		}

		inline bool operator < (const Grid::Point &rhs) const
		{
			// since we use a map in the implementation of search algorithms we need to overload operator <
			// because the map stores the keys in sorted order
			// std::tuple's lexicographic ordering does all the actual work for you
			// and using std::tie means no actual copies are made
			return std::tie(this->x, this->y) < std::tie(rhs.x, rhs.y);
			
		}	

		inline bool operator > (const Grid::Point &rhs) const
		{
			return this->priority > rhs.priority;
;
		}

		
	};
	Grid(int32_t _width, int32_t height);
	~Grid();

	inline int32_t getHeight() { return height; }
	inline int32_t getWidth() { return width; }
	inline std::vector<std::vector<int32_t>>& getGrid() { return grid; }
	void setGridValues(int32_t atWidth, int32_t atHeight, int32_t value);	
	float getCostOfEnteringCell(Point& cell);	
	std::vector<Grid::Point> getAdjacentCells(int32_t x, int32_t y);
	std::vector<Grid::Point> getAdjacentCells(Point& cell);


	void setStartPosition(Grid::Point startPos);
	void setEndPosition(Grid::Point endPos);
	void setObstacle(Grid::Point obstaclePosition);
	void setUntraversable(Grid::Point untraversablePosition);
	void MoveTo(Grid::Point pointToMove);

	void removeCellFromGrid(int32_t atWidth, int32_t atHeight);
	
	// debug
	void printGridState();	
	
 
private:

	// we use a 2D-array to represent a grid. In this case, we're going to use a vector of vectors to represent a 2D array
	// in the example before we used a vector of pointers to arrays to represend a 2D-array for adjacency matrix
	std::vector<std::vector<int32_t>> grid;	
	std::vector<std::vector<std::string>> cells;
	int32_t height = 0;
	int32_t width = 0;

	// visual representation
	const std::string traversable = "O ";
	const std::string untraversable = "  ";
	const std::string moveTo = "- ";
	const std::string obstacle = "# ";
	const std::string start = "S ";
	const std::string end = "E ";
	//const std::string empty = "  ";

	
};

