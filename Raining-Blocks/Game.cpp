#include "Game.h"
#include <algorithm>
#include <thread>
#include <chrono>

Game::Game(sf::RenderWindow& window)
	: b(), queue(), display(20), next(4)
{
	if (!texture.loadFromFile("wallpaper.jpg"))
	{
		throw std::exception("Image not found.");
	}
	background = sf::Sprite(texture);

	window.clear();
	current = queue.dequeue();
	current.setLocation(4, 0, b);

	next[0].setBlockSize(20);
	next[0].setLocation(800, 75);
	for (int i = 1; i < 4; i++)
	{
		next[i].setBlockSize(16);
		next[i].setLocation(810, 200 + 100 * (i - 1));
	}

	window.draw(background);
	for (int i = 0; i < 20; i++)
	{
		display[i] = std::vector<sf::RectangleShape>(12);
		for (int j = 0; j < 10; j++)
		{
			display[i][j] = sf::RectangleShape(sf::Vector2f(50, 50));
			display[i][j].setPosition(500 - 259 + 52 * j, 75 + 52 * i);
			display[i][j].setFillColor(sf::Color(20, 20, 20, 40));
			window.draw(display[i][j]);
		}
	}
	updateNext();
	showNext(window);
	window.display();
}

int Game::start(sf::RenderWindow& window)
{
	clock.restart();

	while (window.isOpen())
	{
		processEvents(window);

		if (clock.getElapsedTime().asSeconds() > sf::seconds(0.5).asSeconds())
		{
			if (!current.translate(Tminos::Tetromino::Direction::DOWN, b)) {
				locked = true;
				current.depositBlocks(b);
			}
			clock.restart();
		}

		if (locked) {
			processLock(window);
		}

		render(window);
	}

	return 0;
}

void Game::updateNext()
{
	for (int i = 0; i < 4; i++)
	{
		next[i].setTetromino(queue.peek(i));
	}
}

void Game::showNext(sf::RenderWindow& window)
{
	for (int i = 0; i < 4; i++)
	{
		next[i].display(window);
	}
}

void Game::render(sf::RenderWindow& window)
{
	window.clear();
	window.draw(background);
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			display[y][x].setFillColor(b[2 + y][1 + x]);
			window.draw(display[y][x]);
		}
	}
	std::pair<int, int> location = current.getLocation();
	for (int x = 0; x < current.getGridSize(); x++)
	{
		for (int y = 0; y < current.getGridSize(); y++)
		{
			if (current[x][y] != 0 && 0 < x + location.first && x + location.first < 11 && 1 < y + location.second && y + location.second < 22)
			{
				display[y + location.second - 2][x + location.first - 1].setFillColor(current.getColor());
				window.draw(display[y + location.second - 2][x + location.first - 1]);
			}
		}
	}
	showNext(window);
	window.display();
}

inline void Game::processEvents(sf::RenderWindow& window)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::KeyPressed:
		{
			bool changed = false;
			switch (event.key.code)
			{
			case sf::Keyboard::Left:
				changed = current.translate(Tminos::Tetromino::Direction::LEFT, b);
				break;

			case sf::Keyboard::Right:
				changed = current.translate(Tminos::Tetromino::Direction::RIGHT, b);
				break;

			case sf::Keyboard::Down:
				changed = current.translate(Tminos::Tetromino::Direction::DOWN, b);
				break;

			case sf::Keyboard::Z:
				changed = current.rotate(Tminos::Tetromino::Direction::LEFT, b);
				break;

			case sf::Keyboard::C:
				changed = current.rotate(Tminos::Tetromino::Direction::RIGHT, b);
				break;

			default:
				break;
			}
			if (changed && inLockPhase)
			{
				clock.restart();
			}
		}

		default:
			break;
		}
	}
}

inline void Game::processLock(sf::RenderWindow& window)
{
	int minLineNum = current.getLocation().second;
	for (int i = minLineNum; i < std::min(minLineNum + current.getGridSize(), 22); i++)
	{
		if (b.isLineClear(i))
		{
			b.removeLine(i);
			for (int j = 0; j < 10; j++)
			{
				display[i - 2][j].setFillColor(sf::Color(20, 20, 20, 200));
				window.draw(display[i - 2][j]);
				window.display();
				window.draw(display[i - 2][j]);
				window.display();
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}
	}
	current = queue.dequeue();
	current.setLocation(4, 0, b);
	updateNext();
	locked = false;
	clock.restart();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1200), "Tetris");
	Game game(window);
	sf::Music music;

	if (!music.openFromFile("tetris.ogg")) {
		return -1;
	}
	
	music.setLoop(true);
	music.play();

	game.start(window);
}