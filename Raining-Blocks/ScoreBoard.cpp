#include "Game.h"

Game::ScoreBoard::ScoreBoard(int x, int y, sf::Font& f)
{
	this->font = f;
	coords = std::pair<int, int>(x, y);

	back = sf::RectangleShape(sf::Vector2f(200, 300));
	back.setPosition(x, y);
	back.setFillColor(sf::Color(20, 20, 20, 100));
	back.setOutlineThickness(3);
	back.setOutlineColor(sf::Color(20, 20, 20, 255));

	scoreLabel.setString("Score");
	linesLabel.setString("Lines Cleared");
	scoreText.setString("0");
	linesText.setString("0");

	scoreLabel.setFont(font);
	scoreLabel.setColor(sf::Color::White);
	scoreLabel.setCharacterSize(30);
	resetOrigin(scoreLabel);

	scoreText.setFont(font);
	scoreText.setColor(sf::Color::White);
	scoreText.setCharacterSize(50);
	resetOrigin(scoreText);

	linesLabel.setFont(font);
	linesLabel.setColor(sf::Color::White);
	linesLabel.setCharacterSize(30);
	resetOrigin(linesLabel);

	linesText.setFont(font);
	linesText.setColor(sf::Color::White);
	linesText.setCharacterSize(50);
	resetOrigin(linesText);

	scoreLabel.setPosition(coords.first + 100, coords.second + 10);
	linesLabel.setPosition(coords.first + 100, coords.second + 150);
	scoreText.setPosition(coords.first + 100, coords.second + 60);
	linesText.setPosition(coords.first + 100, coords.second + 190);

	score = 0;
	lines = 0;
}

void Game::ScoreBoard::addScore(int inc)
{
	score += inc;
	scoreText.setString(std::to_string(score));
	resetOrigin(scoreText);
}

void Game::ScoreBoard::addLines(int inc)
{
	lines += inc;
	linesText.setString(std::to_string(lines));
	resetOrigin(linesText);
}

int Game::ScoreBoard::getScore()
{
	return score;
}

int Game::ScoreBoard::getLines()
{
	return lines;
}

void Game::ScoreBoard::display(sf::RenderWindow& window)
{
	window.draw(back);
	window.draw(scoreLabel);
	window.draw(scoreText);
	window.draw(linesLabel);
	window.draw(linesText);
}

inline void Game::ScoreBoard::resetOrigin(sf::Text& text)
{
	text.setOrigin(sf::Vector2f(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2));
}