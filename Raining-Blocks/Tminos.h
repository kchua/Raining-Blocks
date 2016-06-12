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
		
		enum class Direction {LEFT, RIGHT, DOWN, UP};

		std::pair<int, int> getLocation();
		int getGridSize();
		sf::Color getColor();
		std::vector<int> operator[](int x);
		
		bool setLocation(int x, int y, Board b);
		void depositBlocks(Board& b);
		bool rotate(Direction dir, Board b);
		void resetRotation();
		bool translate(Direction dir, Board b);

	private:
		sf::Color color;
		int gridSize;
		int rotationConfiguration;
		std::vector<std::vector<int>> grid;
		std::pair<int, int> coords;
		bool hasFloorKicked = false;

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