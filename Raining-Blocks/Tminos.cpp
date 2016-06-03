#include "Tminos.h"

namespace Tminos
{
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
		for (int j = 0; j < blocks.size(); j++) {
			grid[j % gridSize][j / gridSize] = blocks[j];
		}
	}

	/* Places a tetromino on a board regardless of validity, but returns a boolean
	   value which indicates whether the location is valid or not.	
	*/
	bool Tminos::Tetromino::setLocation(int x, int y, Board b)
	{
		coords = std::pair<int, int>(x, y);
		return isValidLocation();
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

	
}