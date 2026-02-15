#include "cube.h"
#include "pruning.h"

int main(int argc, char *argv[]) {
	Cube rubiksCube = Cube::create();

	srand(time(0));

	rubiksCube.randomScramble();
	rubiksCube.print();
	rubiksCube.thistlethwaite();
	rubiksCube.print();
	// rubiksCube.print();

	// while (true) {
	// 	std::cout << "Please enter some moves: ";
	//
	// 	std::string input;
	// 	std::cin >> input;
	//
	// 	if (input == "quit") {
	// 		break;
	// 	}
	//
	// 	if (input == "solve") {
	// 		rubiksCube.thistlethwaite();
	// 	}
	//
	// 	if (input == "clear") {
	// 		std::cout << "\x1b[2J\x1b[H";
	// 	} else {
	// 		rubiksCube.executeMoves(input);
	// 	}
	// 	rubiksCube.print();
	// }

	return 0;
}
