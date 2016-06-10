#include "TminoDisplay.h"

TminoDisplay::TminoDisplay()
{

}

void TminoDisplay::setLocation(int x, int y)
{
	coords = std::pair<int, int>(x, y);
}

void TminoDisplay::setTetromino(Tminos::Tetromino tmino)
{
	tetromino = tmino;
	rows = cols = 0;
	for (int i = 0; i < tmino.getGridSize(); i++)
	{
		for (int j = 0; j < tmino.getGridSize(); j++)
		{
			if (tmino[i][j] != 0)
			{
				cols++;
				break;
			}
		}
		for (int j = 0; j < tmino.getGridSize(); j++)
		{
			if (tmino[j][i] != 0)
			{
				rows++;
				break;
			}
		}
	}
}

void TminoDisplay::setBlockSize(int size)
{
	blockSize = size;
}

void TminoDisplay::display(sf::RenderWindow& window)
{
	sf::RectangleShape background(sf::Vector2f(5 * blockSize + 8, 5 * blockSize + 8));
	background.setPosition(coords.first, coords.second);
	background.setFillColor(sf::Color(20, 20, 20, 200));
	window.draw(background);

	int xOrigin = coords.first + (((5 * blockSize + 8) - (cols * (blockSize + 2) - 2)) / 2);
	int yOrigin = coords.second + (((5 * blockSize + 8) - (rows * (blockSize + 2) - 2)) / 2);

	bool emptyLeadingRow = true;

	for (int i = 0; i < tetromino.getGridSize(); i++)
	{
		if (tetromino[i][0] != 0) {
			emptyLeadingRow = false;
		}
	}

	for (int i = 0; i < tetromino.getGridSize(); i++)
	{
		for (int j = (emptyLeadingRow) ? 1 : 0; j < tetromino.getGridSize(); j++)
		{
			if (tetromino[i][j] != 0)
			{
				sf::RectangleShape rectangle(sf::Vector2f(blockSize, blockSize));
				rectangle.setPosition(xOrigin + (blockSize + 2) * i, 
					yOrigin + (blockSize + 2) * (j - ((emptyLeadingRow) ? 1 : 0)));
				rectangle.setFillColor(tetromino.getColor());
				window.draw(rectangle);
			}
		}
	}
}