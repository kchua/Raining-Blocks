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
	Game(sf::RenderWindow& window, sf::Font font);
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

	class ScoreBoard
	{
	public:
		ScoreBoard(int x, int y, sf::Font& f);
		void setPosition(int x, int y);
		void addScore(int inc);
		void addLines(int inc);
		int getScore();
		int getLines();
		int getLevel();
		void display(sf::RenderWindow& window);
	private:
		int score;
		int lines;
		sf::Font font;

		std::pair<int, int> coords;
		sf::RectangleShape back;
		sf::Text scoreLabel;
		sf::Text linesLabel;
		sf::Text levelLabel;
		sf::Text scoreText;
		sf::Text linesText;
		sf::Text levelText;

		void resetOrigin(sf::Text& text);
	} scores;

	void updateNext();
	void showNext(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void processEvents(sf::RenderWindow& window);
	void processLock(sf::RenderWindow& window);

	bool inLockPhase;
	bool locked;
};

#endif