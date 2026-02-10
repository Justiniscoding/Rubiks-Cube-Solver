#include "cube.h"

Cube Cube::create() {
	Cube cube;

	for (int i = 0; i < 8; i++) {
		cube.edgePermutation[i] = i;
		cube.edgeOrientation[i] = 0;
	}

	for (int i = 0; i < 12; i++) {
		cube.cornerPermutation[i] = i;
		cube.cornerOrientation[i] = 0;
	}

	return cube;
}

void Cube::print() { std::string output = ""; }

bool CubeMove::isCompatible(CubeMove *move) {
	if (this->side == move->side) {
		return false;
	}

	return true;
}
