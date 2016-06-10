#include "TetrominoBag.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

TetrominoBag::TetrominoBag()
	: queue()
{
	regenerate();
}

Tminos::Tetromino TetrominoBag::dequeue()
{
	Tminos::Tetromino temp = queue.front();
	queue.pop_front();
	if (queue.size() < 4)
	{
		regenerate();
	}
	return temp;
}

Tminos::Tetromino TetrominoBag::peek(int index)
{
	return queue[index];
}

////////////////////////////
// Private Helper Methods //
////////////////////////////

void TetrominoBag::regenerate()
{
	srand(std::time(0));
	std::vector<Tminos::Tetromino> newSet{ Tminos::I, Tminos::J, Tminos::L, 
		Tminos::O, Tminos::S, Tminos::T, Tminos::Z };
	std::random_shuffle(newSet.begin(), newSet.end());
	for (int i = 0; i < 7; i++)
	{
		queue.push_back(newSet[i]);
	}
}