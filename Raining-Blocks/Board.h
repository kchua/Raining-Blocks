#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <SFML\Graphics\Color.hpp>
#include "DisjointSets.h"

class Board
{
public:
	Board();
	bool isLineClear(int line);
	void removeLine(int line);
	bool occupiedOrOutOfBounds(int x, int y);
	void depositBlock(int x, int y, sf::Color color);
	int getWidth();
	int getHeight();

private:
	std::vector<std::vector<sf::Color>> board;
	std::vector<DisjointSets> lines;
};

#endif