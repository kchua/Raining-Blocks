#include "Tminos.h"

namespace Tminos
{
	//////////////////////////////
	// Public tetromino methods //
	//////////////////////////////

	/* Constructs a tetromino given the gridSize, a 1-D vector indicating which parts of
	   of the grid has blocks, and the color of the blocks. For example:
	   
	   0  0  0
	   1  1  1	  =>  Tetromino(3, {0, 0, 0, 1, 1, 1, 0, 0, 1}, sf::Color::blue);		
	   0  0  1    
	*/
	Tminos::Tetromino::Tetromino(int gridSize, std::vector<int> blocks, sf::Color color)
		: grid(gridSize), gridSize(gridSize), color(color)
	{
		if (gridSize * gridSize != blocks.size())
		{
			throw std::exception("Grid size is inconsistent with the number of blocks.");
		}
		for (int i = 0; i < gridSize; i++)
		{
			grid[i] = std::vector<int>(gridSize);
		}
		for (int j = 0; j < blocks.size(); j++) 
		{
			grid[j % gridSize][j / gridSize] = blocks[j];
		}
	}

	/* Places a tetromino on a board regardless of validity, but returns a boolean
	   value which indicates whether the location is valid or not.	
	*/
	bool Tminos::Tetromino::setLocation(int x, int y, Board b)
	{
		coords = std::pair<int, int>(x, y);
		return isValidLocation(b);
	}

	/* Places all the blocks of a tetromino on a Board. */
	void Tminos::Tetromino::depositBlocks(Board b) 
	{
		for (int i = 0; i < gridSize * gridSize; i++)
		{
			if (grid[i % gridSize][i / gridSize] != 0)
			{
				b.depositBlock(coords.first + (i % gridSize), coords.second + (i / gridSize), color);
			}
		}
	}

	/* Rotates a tetromino if the resulting configuration is valid for the given
	   board; assumes that the tetrimino has an established location, and may
	   result in wall kicks. 
	*/
	void Tminos::Tetromino::rotate(Direction dir, Board b)
	{
		tempRotation(dir);
		if (!isValidLocation(b)) 
		{
			translate(Direction::RIGHT, b);
			if (!isValidLocation(b)) 
			{
				translate(Direction::LEFT, b);
				translate(Direction::LEFT, b);
				if (!isValidLocation(b))
				{
					tempRotation(negate(dir));
				}
			}
		}
	}

	/* Checks if it is possible to shift a tetromino in a certain direction, 
	   then shifts the tetromino if the resulting position is valid.
	*/
	void Tminos::Tetromino::translate(Direction dir, Board b)
	{
		shiftCoords(dir);
		if (!isValidLocation(b)) 
		{
			shiftCoords(negate(dir));
		}
	}


	////////////////////////////////////////
	// Helper methods for Tetromino class //
	////////////////////////////////////////

	/* Convenience function to "negate" a direction */
	Tminos::Tetromino::Direction Tminos::Tetromino::negate(Direction dir) 
	{
		switch (dir)
		{
		case Direction::DOWN:
			return Direction::UP;

		case Direction::UP:
			return Direction::DOWN;

		case Direction::LEFT:
			return Direction::RIGHT;

		default:
			return Direction::RIGHT;
		}
	}

	/* Convenience function to shift coordinates according to a direction. */
	void Tminos::Tetromino::shiftCoords(Direction dir)
	{
		switch (dir)
		{
			case Direction::DOWN:
				coords = std::pair<int, int>(coords.first, coords.second + 1);
				break;

			case Direction::UP:
				coords = std::pair<int, int>(coords.first, coords.second - 1);
				break;

			case Direction::LEFT:
				coords = std::pair<int, int>(coords.first - 1, coords.second);
				break;
				
			case Direction::RIGHT:
				coords = std::pair<int, int>(coords.first + 1, coords.second);
				break;
		}
	}

	/* Checks if the current location of a tetromino is valid. */
	bool Tminos::Tetromino::isValidLocation(Board b)
	{
		for (int i = 0; i < gridSize * gridSize; i++)
		{
			if (grid[i % gridSize][i / gridSize] != 0
				&& b.occupiedOrOutOfBounds(coords.first + (i % gridSize), coords.second + (i / gridSize)))
			{
				return false;
			}
		}
		return true;
	}

	void Tminos::Tetromino::tempRotation(Direction dir) 
	{
		std::vector<std::vector<int>> rotated(gridSize);
		for (int i = 0; i < gridSize; i++) 
		{
			rotated[i] = std::vector<int>(gridSize);
		}
		switch (dir)
		{
			case Direction::LEFT:
				for (int i = 0; i < gridSize * gridSize; i++) {
					int x = i % 4;
					int y = i / 4;
					rotated[y][gridSize - 1 - x] = grid[x][y];
				}
				break;

			case Direction::RIGHT:
				for (int i = 0; i < gridSize * gridSize; i++) {
					int x = i % 4;
					int y = i / 4;
					rotated[gridSize - 1 - y][x] = grid[x][y];
				}
				break;

			default:
				throw std::exception("Invalid direction.");
		}
	}


	///////////////////////////////
	// Standard Tetromino Blocks //
	///////////////////////////////

	Tetromino Tminos::I (4, { 0, 0, 0, 0,
							  0, 0, 0, 0,
						      1, 1, 1, 1,
					          0, 0, 0, 0 }, sf::Color::Cyan);

	Tetromino Tminos::J(3, { 1, 0, 0,
							 1, 1, 1,
							 0, 0, 0 }, sf::Color::Blue);
}