#pragma once
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include "util.h"
#include "maze.h"

/* MazeUF class
 * The class is Union Find set for creating maze.
 */
class MazeUF {
private:
	// for Union Find
	std::vector<uint32> data;
	std::vector<uint32> rank;

	// for maze
	uint32 width, height, size;

	// for Union Find
	int32 root(int32 x);
	bool same(int32 x, int32 y);
	void unite(int32 x, int32 y);

	// Find a different tag cell adjacent to a tag that contains a cell with coordinates (x, y).
	int32 findDifNeighbor(uint32 x, uint32 y, uint32 &outX, uint32 &outY, Direction &outDir);

public:
	MazeUF(uint32 width, uint32 height);

	// findDifneighbor() and unite
	void uniteDifNeighbor(uint32 x, uint32 y, uint32 &outX, uint32 &outY, Direction &outDir);

	bool isAllSame();
};