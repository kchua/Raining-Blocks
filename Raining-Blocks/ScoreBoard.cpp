#include "Game.h"

Game::ScoreBoard::ScoreBoard(int x, int y, sf::Font& f)
{
	this->font = f;

	back = sf::RectangleShape(sf::Vector2f(x, y));
	back.setFillColor(sf::Color(20, 20, 20, 100));
	back.setOutlineThickness(3);
	back.setOutlineColor(sf::Color::White);

	scoreLabel.setString("Score");
	linesLabel.setString("Lines Cleared");
	levelLabel.setString("Level");
	scoreText.setString("0");
	linesText.setString("0");
	levelText.setString("1");

	scoreLabel.setFont(font);
	scoreLabel.setColor(sf::Color::White);
	scoreLabel.setCharacterSize(50);
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

	levelLabel.setFont(font);
	levelLabel.setColor(sf::Color::White);
	levelLabel.setCharacterSize(50);
	resetOrigin(levelLabel);

	levelText.setFont(font);
	levelText.setColor(sf::Color::White);
	levelText.setCharacterSize(50);
	resetOrigin(levelText);

	score = 0;
	lines = 0;
}

void Game::ScoreBoard::setPosition(int x, int y)
{
	coords = std::pair<int, int>(x, y);
	back.setPosition(sf::Vector2f(x, y));

	int xOffset = back.getLocalBounds().width / 2;
	scoreLabel.setPosition(coords.first + xOffset, coords.second + 20);
	linesLabel.setPosition(coords.first + xOffset, coords.second + 160);
	levelLabel.setPosition(coords.first + xOffset, coords.second + 310);
	scoreText.setPosition(coords.first + xOffset, coords.second + 75);
	linesText.setPosition(coords.first + xOffset, coords.second + 210);
	levelText.setPosition(coords.first + xOffset, coords.second + 370);
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
	levelText.setString(std::to_string(1 + (lines / 10)));
	resetOrigin(linesText);
	resetOrigin(levelText);
}

int Game::ScoreBoard::getScore()
{
	return score;
}

int Game::ScoreBoard::getLines()
{
	return lines;
}

int Game::ScoreBoard::getLevel()
{
	return 1 + (lines / 10);
}

void Game::ScoreBoard::display(sf::RenderWindow& window)
{
	window.draw(back);
	window.draw(scoreLabel);
	window.draw(scoreText);
	window.draw(linesLabel);
	window.draw(linesText);
	window.draw(levelLabel);
	window.draw(levelText);
}

inline void Game::ScoreBoard::resetOrigin(sf::Text& text)
{
	text.setOrigin(sf::Vector2f(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2));
}