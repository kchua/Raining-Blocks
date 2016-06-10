#ifndef TMINODISPLAY_H
#define TMINODISPLAY_H

#include "Tminos.h"
#include <SFML/Graphics.hpp>

class TminoDisplay
{
public:
	TminoDisplay();

	void setLocation(int x, int y);
	void setTetromino(Tminos::Tetromino tmino);
	void setBlockSize(int size);

	void display(sf::RenderWindow& window);

private:
	Tminos::Tetromino tetromino = Tminos::O;
	int rows; int cols;
	std::pair<int, int> coords;
	int blockSize;
};

#endif