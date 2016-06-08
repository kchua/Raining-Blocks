#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Board.h"
#include "Tminos.h"

class GameState
{
public:
	GameState();
private:
	Board board;
	Tminos::Tetromino current;

};

#endif