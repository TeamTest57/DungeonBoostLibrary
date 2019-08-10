#include <iostream>
#include "maze.h"

constexpr uint_fast32_t WIDTH = 10;
constexpr uint_fast32_t HEIGHT = 10;

int main() {
	Maze maze(WIDTH, HEIGHT);

	maze.print();

	return 0;
}