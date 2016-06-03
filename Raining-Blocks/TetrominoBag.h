#ifndef TETROMINOBAG_H
#define TETROMINOBAG_H

#include <vector>
#include "Tminos.h"

class TetrominoBag
{
public:
	TetrominoBag();
	Tminos::Tetromino dequeue();
	Tminos::Tetromino peek(int num);
private:
	std::vector<Tminos::Tetromino> queue;
	void regenerate();
};

#endif 