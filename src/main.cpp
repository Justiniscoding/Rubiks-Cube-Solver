#include "cube.h"

int main(int argc, char *argv[]) {
	Cube rubiksCube = Cube::create();

	srand(time(0));

	// generateThistlethwaiteTables();

	// rubiksCube.randomScramble();
	rubiksCube.executeMoves("U2 D2 L U2 L U B2 D L2 D2 U' B D2 U2 R2 B U2 R2 "
							"B2 U2 F U2 F' L F2 U R' B' F' U2");

	rubiksCube.print();
	rubiksCube.thistlethwaite();
	rubiksCube.print();
	// rubiksCube.print();
	// rubiksCube.kociemba();
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
