#include "Game.h"
#include <algorithm>
#include <thread>
#include <chrono>

Game::Game(sf::RenderWindow& window, sf::Font font)
	: b(), queue(), display(20), next(4), scores(200, 450, font)
{
	const int blockSize = 48;                                                             // Reduce magic numbers, easy window resizing.
	const int largeDisplaySize = 30;
	const int smallDisplaySize = 20;
	const int blockMargin = 4;
	constexpr int halfField = (10 * blockSize + 9 * blockMargin) / 2;
	int screenMiddle = window.getSize().x / 2;
	int largeDisplayOffset = (screenMiddle - halfField - (5 * largeDisplaySize)) / 2;

	if (!texture.loadFromFile("wallpaper.jpg"))											  // Load wallpaper
	{
		throw std::exception("Image not found.");
	}
	background = sf::Sprite(texture);

	scores.setPosition((screenMiddle - halfField - 200) / 2, 500);

	current = queue.dequeue();
	updateNext();
	current.setLocation(4, 0, b);

	next[0].setBlockSize(largeDisplaySize);
	next[0].setLocation(halfField + screenMiddle + largeDisplayOffset, 200);
	for (int i = 1; i < 4; i++)
	{
		next[i].setBlockSize(smallDisplaySize);
		next[i].setLocation(
			halfField + screenMiddle + largeDisplayOffset + 5 * (largeDisplaySize - smallDisplaySize) / 2,
			375 + 125 * (i - 1));
	}

	hold.setBlockSize(largeDisplaySize);
	hold.setLocation(largeDisplayOffset, 200);

	window.clear();
	window.draw(background);
	for (int i = 0; i < 20; i++)
	{
		display[i] = std::vector<sf::RectangleShape>(12);
		for (int j = 0; j < 10; j++)
		{
			display[i][j] = sf::RectangleShape(sf::Vector2f(blockSize, blockSize));
			display[i][j].setPosition(
				screenMiddle - halfField + (blockMargin + blockSize) * j,
				75 + (blockMargin + blockSize) * i);
			display[i][j].setFillColor(sf::Color(20, 20, 20, 100));
			window.draw(display[i][j]);
		}
	}
	showNext(window);
	scores.display(window);
	window.display();
}

int Game::start(sf::RenderWindow& window)
{
	clock.restart();

	while (window.isOpen())
	{
		processEvents(window);

		if (!inLockPhase && clock.getElapsedTime().asSeconds() > sf::seconds(0.5).asSeconds())
		{
			current.translate(Tminos::Tetromino::Direction::DOWN, b);
			if (!currentMovableUnderGravity())
			{
				inLockPhase = true;
			}
			clock.restart();
		}

		if (inLockPhase) {
			if (clock.getElapsedTime().asSeconds() > sf::seconds(0.5).asSeconds())
			{
				current.depositBlocks(b);
				processLock(window);
				inLockPhase = false;
				usedHold = false;
				clock.restart();
			}
			else
			{
				if (currentMovableUnderGravity()) 
				{
					inLockPhase = false;
				}
			}
		}

		render(window);
	}

	return 0;
}

inline void Game::updateNext()
{
	for (int i = 0; i < 4; i++)
	{
		next[i].setTetromino(queue.peek(i));
	}
}

inline void Game::showNext(sf::RenderWindow& window)
{
	for (int i = 0; i < 4; i++)
	{
		next[i].display(window);
	}
}

inline void Game::render(sf::RenderWindow& window)
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
	hold.display(window);
	scores.display(window);
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
				if (changed)
				{
					scores.addScore(10);
					clock.restart();
				}
				break;

			case sf::Keyboard::Z:
				changed = current.rotate(Tminos::Tetromino::Direction::LEFT, b);
				break;

			case sf::Keyboard::C:
				changed = current.rotate(Tminos::Tetromino::Direction::RIGHT, b);
				break;

			case sf::Keyboard::X:
				if (!usedHold)
				{
					current.resetRotation();
					if (!hold.hasContents()) {
						hold.setTetromino(current);
						current = queue.dequeue();
						updateNext();
					}
					else
					{
						Tminos::Tetromino temp = hold.getTetromino();
						hold.setTetromino(current);
						current = temp;
					}

					if (!current.setLocation(4, 0, b)) // Game Over
					{
						window.close();
					}
					changed = true;
					usedHold = true;
					clock.restart();
				}

			default:
				break;
			}

			if (inLockPhase && changed)
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
	for (int i = std::max(minLineNum, 2); i < std::min(minLineNum + current.getGridSize(), 22); i++)
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
			scores.addLines(1);
		}
	}
	current = queue.dequeue();
	if (!current.setLocation(4, 0, b)) // Game Over
	{
		window.close();
	}
	updateNext();
	inLockPhase = false;
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	clock.restart();
}

inline bool Game::currentMovableUnderGravity()
{
	if (!current.translate(Tminos::Tetromino::Direction::DOWN, b))
	{
		return false;
	}
	else
	{
		current.translate(Tminos::Tetromino::Direction::UP, b);
		return true;
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1300, 1200), "Tetris");
	sf::Music music;
	sf::Font font;

	if (!music.openFromFile("tetris.ogg")) {
		return -1;
	}

	if (!font.loadFromFile("Gasalt-Regular.ttf")) {
		return -1;
	}
	
	music.setLoop(true);
	music.play();

	Game game(window, font);

	game.start(window);
}