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

		enum class Direction {LEFT, RIGHT, DOWN};

		void rotate(Direction dir);
		void translate(Direction dir);
	private:
		sf::Color color;
		int gridSize;
		std::vector<std::vector<int>> grid;
		std::pair<int, int> coords;

		bool isValidLocation();
		void tempRL();
		void tempRR();
	};

	const Tetromino I;
	const Tetromino J;
	const Tetromino L;
	const Tetromino O;
	const Tetromino T;
	const Tetromino S;
	const Tetromino Z;
}
#endif