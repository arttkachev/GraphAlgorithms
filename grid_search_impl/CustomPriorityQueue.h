#pragma once
#include <vector>
#include <map>
#include "Grid.h"
#include <iostream>


class CustomPriorityQueue
{
public:
	CustomPriorityQueue();
	~CustomPriorityQueue();

	void enqueue(Grid::Point element, float priority);
	Grid::Point dequeue();
	bool isEmpty();

private:
	std::map <Grid::Point, float> _list;
};





