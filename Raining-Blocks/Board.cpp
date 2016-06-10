#include "Board.h"
#include <iostream>

/* Constructor for the board class. */
Board::Board()
	: board(23), lines(20)
{
	for (int i = 0; i < 23; i++)
	{
		board[i] = std::vector<sf::Color>(12);
		board[i][0] = board[i][11] = sf::Color(255, 255, 255, 0);	
	}
	for (int i = 0; i < 12; i++)
	{
		board[22][i] = sf::Color(255, 255, 255, 0);
	}
	for (int i = 1; i < 11; i++)
	{
		for (int j = 0; j < 22; j++)
		{
			board[j][i] = sf::Color(20, 20, 20, 40);
		}
	}
	for (int i = 0; i < 20; i++)
	{
		lines[i] = DisjointSets(12);
	}
}

/* Checks if the LINENUM line is cleared. */
bool Board::isLineClear(int lineNum) 
{
	if (lineNum >= 20)
	{
		throw std::exception("Invalid line number.");
	}
	return lines[lineNum].isConnected(0, 11);
}

/* Removes the LINENUM line (does not check if the line has been cleared). */
void Board::removeLine(int lineNum) 
{
	for (int i = lineNum; i > 0; i--)
	{
		lines[i] = lines[i - 1];
		board[2 + i] = board[1 + i];
	}
	lines[0] = DisjointSets(12);
	board[0] = std::vector<sf::Color>(12);
	board[0][0] = board[0][11] = sf::Color::Black;
}

/* Checks if the space with the given coordinates is empty or 
   out of bounds.*/
bool Board::occupiedOrOutOfBounds(int x, int y) 
{
	if (x < 12 && y < 23)
	{
		return board[y][x] != sf::Color(20, 20, 20, 40);
	}
	return true;
}

/* Places a block in the given space (does not check if there is
   another block in the given coordinate). */
void Board::depositBlock(int x, int y, sf::Color color)
{
	board[y][x] = color;
}

std::vector<sf::Color> Board::operator[](int y)
{
	return board[y];
}

