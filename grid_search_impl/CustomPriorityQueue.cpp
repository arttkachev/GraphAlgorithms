#include "stdafx.h"
#include "CustomPriorityQueue.h"

CustomPriorityQueue::CustomPriorityQueue()
{
}


CustomPriorityQueue::~CustomPriorityQueue()
{
}


void CustomPriorityQueue::enqueue(Grid::Point element, float priority)
{
	_list[element] = priority;
}


Grid::Point CustomPriorityQueue::dequeue()

{
	
	if (!_list.empty())
	{
		std::map <Grid::Point, float>::iterator it = _list.begin();
		it->first;
		Grid::Point best = it->first;
		float priority = _list[best];
		std::vector <Grid::Point> keys;


		for (std::map <Grid::Point, float>::iterator iter = _list.begin(); iter != _list.end(); iter++)
		{
			keys.push_back(iter->first);
		}


		for (Grid::Point candidate : keys)
		{
			if (_list[candidate] < priority)
			{
				best = candidate;
				priority = _list[candidate];
			}
		}
		_list.erase(best);
		return best;
	}
	
}


bool CustomPriorityQueue::isEmpty()
{
	return _list.empty();
}


