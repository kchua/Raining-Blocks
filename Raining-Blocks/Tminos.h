#ifndef TMINOS_H
#define TMINOS_H

#include <vector>
#include <SFML\Graphics\Color.hpp>
#include "Board.h"

namespace Tminos 
{
	class Tetromino 
	{
	public:
		Tetromino(int gridSize, std::vector<int> blocks, sf::Color color);
		bool setLocation(int x, int y, Board b);
		void depositBlocks(Board b);

		enum class Direction {LEFT, RIGHT, DOWN, UP}; // Up is for reversal only

		void rotate(Direction dir, Board b);
		void translate(Direction dir, Board b);
	private:
		sf::Color color;
		int gridSize;
		std::vector<std::vector<int>> grid;
		std::pair<int, int> coords;

		Direction negate(Direction dir);
		void shiftCoords(Direction dir);
		bool isValidLocation(Board b);
		void tempRotation(Direction dir);
	};

	extern Tetromino I;
	extern Tetromino J;
	extern Tetromino L;
	extern Tetromino O;
	extern Tetromino T;
	extern Tetromino S;
	extern Tetromino Z;
}
#endif