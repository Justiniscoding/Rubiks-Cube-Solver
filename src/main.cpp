#include <cube.h>

int main(int argc, char *argv[]) {
	Cube rubiksCube = Cube::create();

	CubeMove move;

	move.side = RIGHT;
	move.amount = 1;

	rubiksCube.rotateSide(&move);

	rubiksCube.print();

	return 0;
}
