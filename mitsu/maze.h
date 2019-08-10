#pragma once
#include <iostream>
#include <vector>
#include "util.h"

/* Cell class
 * The data is used as one element of maze.
 */
enum CellType: uint32 {
	CELLTYPE_ROAD, CELLTYPE_WALL
};

class Cell {
private:
	uint32 x, y;
	CellType type;

public:
	Cell(uint32 x, uint32 y, CellType type): x(x), y(y), type(type) {
	}

	void print() const {
		if(type == CELLTYPE_ROAD) std::cout << "  ";
		if(type == CELLTYPE_WALL) std::cout << "**";
	}
};

/* Maze class
 * The class manages entire maze.
 */
class Maze {
	uint32 width, height;
	std::vector<Cell> data;

	inline const Cell *at(uint32 x, uint32 y) const {
		return &data[width * y + x];
	}

public:
	Maze(uint32 width, uint32 height);		// Initialize CELLTYPE_WALL
	Maze(uint32 width, uint32 height, std::vector<CellType> cellTypes);

	void print() const;
};
