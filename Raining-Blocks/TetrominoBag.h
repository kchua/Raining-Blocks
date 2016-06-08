#ifndef TETROMINOBAG_H
#define TETROMINOBAG_H

#include <deque>
#include "Tminos.h"

class TetrominoBag
{
public:
	TetrominoBag();
	Tminos::Tetromino dequeue();
	Tminos::Tetromino peek(int index);
private:
	std::deque<Tminos::Tetromino> queue;
	void regenerate();
};

#endif 