#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <SFML\Graphics\Color.hpp>
#include "DisjointSets.h"

class Board
{
public:
	Board();
	bool isLineClear(int lineNum);
	void removeLine(int lineNum);
	bool occupiedOrOutOfBounds(int x, int y);
	void depositBlock(int x, int y, sf::Color color);

private:
	std::vector<std::vector<sf::Color>> board;
	std::vector<DisjointSets> lines;
};

#endif