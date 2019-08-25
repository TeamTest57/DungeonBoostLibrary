#pragma once
#include <array>
#include <iostream>
using Matrix = std::array<std::array<int, 32>, 24>;//MatrixŒ^‚Ì’è‹`

class Maze {
public:
  void Draw(Matrix& matrix) {//“ñŽŸŒ³”z—ñ‚Ì•`‰æ
	for (int y = 0; y < 24; y++) {
	  for (int x = 0; x < 32; x++) {
		std::cout << matrix[y][x];
	  }
	  std::cout << std::endl;
	}
  }
};