#include "Game.h"
#include <algorithm>

Game::Game(sf::RenderWindow& window)
	: b(), queue(), display(20)
{
	window.clear(sf::Color::White);
	current = queue.dequeue();
	current.setLocation(4, 0, b);

	for (int i = 0; i < 20; i++)
	{
		display[i] = std::vector<sf::RectangleShape>(12);
		for (int j = 0; j < 10; j++)
		{
			display[i][j] = sf::RectangleShape(sf::Vector2f(50, 50));
			display[i][j].setPosition(400 - 259 + 52 * j, 52 * i);
			window.draw(display[i][j]);
		}
	}
	window.display();
}

int Game::start(sf::RenderWindow& window)
{
	sf::Clock clock;

	while (window.isOpen())
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

		/*
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			current.translate(Tminos::Tetromino::Direction::LEFT, b);V
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			current.translate(Tminos::Tetromino::Direction::RIGHT, b);
		}*/
		
		if (clock.getElapsedTime().asSeconds() > sf::seconds(0.5).asSeconds())
		{
			if (!current.translate(Tminos::Tetromino::Direction::DOWN, b)) {
				locked = true;
				current.depositBlocks(b);
			}
			clock.restart();
		}

		if (locked) {
			// Animations and line clearing go here.
			int minLineNum = current.getLocation().second;
			for (int i = minLineNum; i < std::min(minLineNum + current.getGridSize(), 22); i++)
			{
				if (b.isLineClear(i))
				{
					b.removeLine(i);
				}
			}
			current = queue.dequeue();
			current.setLocation(4, 0, b);
			locked = false;
			clock.restart();
		}

		render(window);
	}

	return 0;
}

void Game::render(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
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
	window.display();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 1200), "Tetris");
	Game game(window);
	sf::Music music;

	if (!music.openFromFile("tetris.ogg")) {
		return -1;
	}
	
	music.setLoop(true);
	music.play();

	game.start(window);
}