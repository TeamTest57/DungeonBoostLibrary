#include "clustering_maze.h"

MazeUF::MazeUF(uint32 width, uint32 height): width(width), height(height), size(width *height) {
	data = std::vector<uint32>(size);
	rank = std::vector<uint32>(size, 0);
	for(size_t i = 0; i < size; i++) data[i] = i;
}

int32 MazeUF::root(int32 x) {
	return data[x] == x ? x : data[x] = root(data[x]);
}

bool MazeUF::same(int32 x, int32 y) {
	return root(x) == root(y);
}

void MazeUF::unite(int32 x, int32 y) {
	x = root(x);
	y = root(y);
	if(x == y) return;

	if(rank[x] < rank[y]) data[x] = y;
	else {
		data[y] = x;
		if(rank[x] == rank[y]) rank[x]++;
	}
}

bool MazeUF::isAllSame() {
	for(size_t i = 1; i < data.size(); i++) if(!same(i, 0)) return false;
	return true;
}

int32 MazeUF::findDifNeighbor(uint32 x, uint32 y, uint32 &outX, uint32 &outY, Direction &outDir) {
	std::vector<uint32> sameTags;
	uint32 cellind = y * width + x;
	for(size_t i = 0; i < size; i++)
		if(same(cellind, i)) sameTags.emplace_back(i);
	random_shuffle(sameTags.begin(), sameTags.end());

	uint32 cell1X, cell1Y, cell2X, cell2Y, cell2ind;
	std::vector<Direction> dirs = {UP_DIR, RIGHT_DIR, DOWN_DIR, LEFT_DIR};
	for(auto cell1ind: sameTags) {
		cell1X = cell1ind % width;
		cell1Y = cell1ind / width;
		random_shuffle(dirs.begin(), dirs.end());
		for(auto dir: dirs) {
			if((dirDx(dir) < 0 && cell1X == 0) || (dirDx(dir) > 0 && cell1X == width - 1)) continue;
			cell2X = cell1X + dirDx(dir);
			if((dirDy(dir) < 0 && cell1Y == 0) || (dirDy(dir) > 0 && cell1Y == height - 1)) continue;
			cell2Y = cell1Y + dirDy(dir);
			cell2ind = cell2Y * width + cell2X;
			if(!same(cell1ind, cell2ind)) {
				outX = cell2X;
				outY = cell2Y;
				outDir = dir;
				return 0;
			}
		}
	}
	return -1;
}

void MazeUF::uniteDifNeighbor(uint32 x, uint32 y, uint32 &outX, uint32 &outY, Direction &outDir) {
	uint32 oX, oY;
	Direction oDir;
	if(findDifNeighbor(x, y, oX, oY, oDir) != -1) unite(y * width + x, oY * width + oX);
	outX = oX;
	outY = oY;
	outDir = oDir;
}

ClusteringMaze::ClusteringMaze(uint32 width, uint32 height): width(width), height(height), size(width *height) {
	std::random_device seed;
	randomEngine = std::mt19937(seed());
}

std::vector<CellType> ClusteringMaze::create() {
	if(width % 2 == 0) width--;
	if(height % 2 == 0) height--;
	
	MazeUF sets(width / 2, height / 2);
	uint32 randCellX, randCellY;

	// base
	std::vector<CellType> baseMaze(size, CELLTYPE_WALL);
	for(size_t i = 0; i < width / 2; i++) {
		for(size_t j = 0; j < height / 2; j++) {
			baseMaze[width * (2 * j + 1) + (2 * i + 1)] = CELLTYPE_ROAD;
		}
	}

	uint32 outX, outY;
	Direction outDir;
	while(!sets.isAllSame()) {
		randCellX = randomEngine() % (width / 2);
		randCellY = randomEngine() % (height / 2);

		sets.uniteDifNeighbor(randCellX, randCellY, outX, outY, outDir);

		// break wall
		baseMaze[(2 * outY + 1) * width + (2 * outX + 1) - dirDy(outDir) * width - dirDx(outDir)] = CELLTYPE_ROAD;
	}

	return baseMaze;
}
