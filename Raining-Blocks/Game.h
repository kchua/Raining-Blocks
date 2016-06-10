#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Tminos.h"
#include "TetrominoBag.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game
{
public:
	Game(sf::RenderWindow& window);
	int start(sf::RenderWindow& window);

private:
	sf::RenderWindow window;

	Board b;
	TetrominoBag queue;
	Tminos::Tetromino current = Tminos::O; // dummy Tetromino

	std::vector<std::vector<sf::RectangleShape>> display;
	void render(sf::RenderWindow& window);

	bool inLockPhase;
	bool locked;
};

#endif