#include "Game.h"

Game::Game(sf::RenderWindow& window)
	: b(), queue(), display(20)
{
	window.clear();
	current = queue.dequeue();
	for (int i = 0; i < 20; i++)
	{
		display[i] = std::vector<sf::RectangleShape>(12);
		for (int j = 0; j < 12; j++)
		{
			display[i][j] = sf::RectangleShape(sf::Vector2f(30, 30));
			display[i][j].setPosition(400 - 191 + 32 * j, 32 * i);
			window.draw(display[i][j]);
		}
	}
	window.display();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Tetris");
	Game game(window);
	sf::Music music;

	if (!music.openFromFile("tetris.ogg")) {
		return -1;
	}
	
	music.setLoop(true);
	music.play();

	while (true) {

	}
	1000 + 1000;
}