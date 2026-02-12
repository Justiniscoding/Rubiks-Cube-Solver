#include <cube.h>
#include <iostream>

int main(int argc, char *argv[]) {
	Cube rubiksCube = Cube::create();

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
	// 	if (input == "clear") {
	// 		std::cout << "\x1b[2J\x1b[H";
	// 	} else {
	// 		rubiksCube.executeMoves(input);
	//
	// 		rubiksCube.print();
	// 	}
	// }

	std::cout << "First t perm:\n";

	rubiksCube.executeMoves("R U R' U' R' F R2 U' R' U' R U R' F'");

	rubiksCube.print();

	std::cout << "Second t perm:\n";

	rubiksCube.executeMoves("R U R' U' R' F R2 U' R' U' R U R' F'");

	rubiksCube.print();

	return 0;
}
