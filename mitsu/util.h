#pragma once
#include <iostream>

// ------ Type definitions ----------
typedef int_fast32_t int32;
typedef uint_fast32_t uint32;

enum Direction: uint32 {
	UP_DIR, RIGHT_DIR, DOWN_DIR, LEFT_DIR
};

int32 dirDx(Direction dir);
int32 dirDy(Direction dir);