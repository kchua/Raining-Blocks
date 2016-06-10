#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Tminos.h"
#include "TetrominoBag.h"
#include "TminoDisplay.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game
{
public:
	Game(sf::RenderWindow& window);
	int start(sf::RenderWindow& window);

private:
	sf::Texture texture;
	sf::Sprite background;
	sf::RenderWindow window;
	sf::Clock clock;
	std::vector<std::vector<sf::RectangleShape>> display;

	Board b;
	TetrominoBag queue;
	Tminos::Tetromino current = Tminos::O; // dummy Tetromino

	std::vector<TminoDisplay> next;

	TminoDisplay hold;
	bool usedHold;

	void updateNext();
	void showNext(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void processEvents(sf::RenderWindow& window);
	void processLock(sf::RenderWindow& window);

	bool inLockPhase;
	bool locked;
};

#endif