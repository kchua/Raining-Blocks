#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Board.h"
#include "Tminos.h"
#include "TetrominoBag.h"
#include <vector>

class GameState
{
public:
	GameState();
	void gravity();
	void lock();
	int getScore();
	int getNumLinesCleared();
	
private:
	Board board;
	Tminos::Tetromino current;
	TetrominoBag queue;
	bool inLockPhase;

	bool clearedLines;
	std::vector<int> linesCleared;

	int numLinesCleared;
	int score;
};

#endif