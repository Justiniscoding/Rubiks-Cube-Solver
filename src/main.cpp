#include "cube.h"
#include "solver.h"

int main(int argc, char *argv[]) {
	Cube rubiksCube = Cube::create();

	srand(time(0));

	Solver cubeSolver;
	cubeSolver.init(THISTLETHWAITE, false);

	clock_t start, end;

	start = clock();
	for (int i = 0; i < 3000; i++) {
		rubiksCube.randomScramble(false);
		cubeSolver.solveCube(rubiksCube);
	}
	end = clock();
	printf("It took %f seconds to solve all of the cubes!\n",
		   (double)(end - start) / CLOCKS_PER_SEC);

	return 0;
}
