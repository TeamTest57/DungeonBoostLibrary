#include "util.h"

int32 dirDx(Direction dir) {
	switch(dir) {
	case UP_DIR:
	case DOWN_DIR:
		return 0;
	case RIGHT_DIR:
		return 1;
	case LEFT_DIR:
		return -1;
	}
}

int32 dirDy(Direction dir) {
	switch(dir) {
	case RIGHT_DIR:
	case LEFT_DIR:
		return 0;
	case UP_DIR:
		return -1;
	case DOWN_DIR:
		return 1;
	}
}