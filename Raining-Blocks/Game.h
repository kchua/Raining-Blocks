#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Tminos.h"
#include "TetrominoBag.h"
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game(sf::RenderWindow* window);
	int start();

private:
	sf::RenderWindow window;

	Board b;
	TetrominoBag queue;
	Tminos::Tetromino current;

	std::vector<std::vector<sf::RectangleShape>> display;
};

#endif