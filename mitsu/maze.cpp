#include "maze.h"

Maze::Maze(uint32 width, uint32 height): width(width), height(height) {
	for(size_t i = 0; i < height; i++) {
		for(size_t j = 0; j < width; j++)
			data.emplace_back(j, i, CELLTYPE_WALL);
	}
}

Maze::Maze(uint32 width, uint32 height, std::vector<CellType> cellTypes): width(width), height(height) {
	for(size_t i = 0; i < height; i++) {
		for(size_t j = 0; j < width; j++)
			data.emplace_back(j, i, cellTypes[width * i + j]);
	}
}

void Maze::print() const {
	for(size_t i = 0; i < height; i++) {
		for(size_t j = 0; j < width; j++) at(j, i)->print();
		std::cout << "\n";
	}
}