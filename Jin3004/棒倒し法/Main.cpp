//(c) 2019 written by Jin3004

#include "Maze.hpp"
#include <iostream>
#include <random>

#define debug(var) std::cout << #var << ": " << var << std::endl

int main() {

  int H, W; std::cin >> H >> W;//H -> 迷路の高さ W -> 迷路の横の長さ
  Matrix matrix(H, std::vector<int>(W));//0 -> 通路 1 -> 壁

  Maze maze;

  for (int y = 0; y < H; y++)for (int x = 0; x < W; x++) {
	if (x == 0 || x == W - 1 || y == 0 || y == H - 1) {
	  matrix[y][x] = 1;
	}
	else if (x % 2 == 0 && x < W - 2 && y % 2 == 0 && y < H - 2)matrix[y][x] = 1;
	else matrix[y][x] = 0;
  }

  int dx[4] = { 1, 0, -1, 0 }, dy[4] = { 0, 1, 0, -1 };//4つのベクトルを用意しておく
  std::mt19937 mt{ std::random_device{}() };
  std::uniform_int_distribution<int> dist1(0, 3);//operator()で0 ~ 3の乱数を返す(1行目用)
  std::uniform_int_distribution<int> dist2(0, 2);//0 ~ 2の乱数を返す(2行目以降用)

  for (int y = 2; y < H - 2; y += 2)for (int x = 2; x < W - 2; x += 2) {
	for (int i = 0; i < 4; i++) {
	  int direction = -1;
	  if (y == 2)direction = dist1(mt);
	  else direction = dist2(mt);
	  if (matrix[y + dy[direction]][x + dx[direction]] == 0) {
		matrix[y + dy[direction]][x + dx[direction]] = 1;
		break;
	  }
	}
  }
  maze.Draw(matrix);

  return 0;
}