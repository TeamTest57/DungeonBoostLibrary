#include <iostream>
#include "clustering_maze.h"

constexpr uint_fast32_t WIDTH = 47;
constexpr uint_fast32_t HEIGHT = 47;

int main() {
	ClusteringMaze maze(WIDTH, HEIGHT);

	maze().print();

	return 0;
}