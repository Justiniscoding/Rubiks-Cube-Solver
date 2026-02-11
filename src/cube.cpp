#include "cube.h"
#include <cstdint>
#include <iostream>

Cube Cube::create() {
	Cube cube;

	for (int i = 0; i < 12; i++) {
		cube.edgePermutation[i] = i;
		cube.edgeOrientation[i] = 0;
	}

	for (int i = 0; i < 8; i++) {
		cube.cornerPermutation[i] = i;
		cube.cornerOrientation[i] = 0;
	}

	return cube;
}

std::string getColorString(char edge) {
	std::string s = "\033[38;5;";

	if (edge == 'U') {
		s += "231mW";
	} else if (edge == 'D') {
		s += "226mY";
	} else if (edge == 'F') {
		s += "83mG";
	} else if (edge == 'R') {
		s += "196mR";
	} else if (edge == 'L') {
		s += "208mO";
	} else if (edge == 'B') {
		s += "21mB";
	}

	s += "\033[0m";

	return s;
}

std::string Cube::getPiece(PieceType type, uint8_t pieceIndex,
						   uint8_t faceIndex) {
	char s = ' ';

	if (type == EDGE) {
		std::string edge = edges[edgePermutation[pieceIndex]];

		s = edge[(faceIndex + edgeOrientation[pieceIndex]) % 2];
	} else if (type == CORNER) {
		std::string corner = corners[cornerPermutation[pieceIndex]];

		s = corner[(faceIndex + cornerOrientation[pieceIndex]) % 3];
	}

	return getColorString(s);
}

void Cube::print() {
	std::string output = "";

	std::string faceOffset = "      ";

	output += faceOffset + getPiece(CORNER, 7, 1) + " ";
	output += getPiece(EDGE, 10, 1) + " ";
	output += getPiece(CORNER, 6, 2);
	output += "\n";

	output += faceOffset + getPiece(EDGE, 7, 0) + " ";
	output += getColorString('B') + " ";
	output += getPiece(EDGE, 6, 0);
	output += "\n";

	output += faceOffset + getPiece(CORNER, 0, 2) + " ";
	output += getPiece(EDGE, 0, 1) + " ";
	output += getPiece(CORNER, 1, 1);
	output += "\n";

	output += getPiece(CORNER, 7, 2) + " ";
	output += getPiece(EDGE, 7, 1) + " ";
	output += getPiece(CORNER, 0, 1);
	output += " ";

	output += getPiece(CORNER, 0, 0) + " ";
	output += getPiece(EDGE, 0, 0) + " ";
	output += getPiece(CORNER, 1, 0);
	output += " ";

	output += getPiece(CORNER, 1, 2) + " ";
	output += getPiece(EDGE, 6, 1) + " ";
	output += getPiece(CORNER, 6, 1);
	output += " ";

	output += getPiece(CORNER, 6, 0) + " ";
	output += getPiece(EDGE, 10, 0) + " ";
	output += getPiece(CORNER, 7, 0);
	output += "\n";

	output += getPiece(EDGE, 11, 1) + " ";
	output += getColorString('L') + " ";
	output += getPiece(EDGE, 3, 1);
	output += " ";

	output += getPiece(EDGE, 3, 0) + " ";
	output += getColorString('U') + " ";
	output += getPiece(EDGE, 1, 0);
	output += " ";

	output += getPiece(EDGE, 1, 1) + " ";
	output += getColorString('R') + " ";
	output += getPiece(EDGE, 9, 1);
	output += " ";

	output += getPiece(EDGE, 9, 0) + " ";
	output += getColorString('D') + " ";
	output += getPiece(EDGE, 11, 0);
	output += "\n";

	output += getPiece(CORNER, 4, 1) + " ";
	output += getPiece(EDGE, 4, 1) + " ";
	output += getPiece(CORNER, 3, 2);
	output += " ";

	output += getPiece(CORNER, 3, 0) + " ";
	output += getPiece(EDGE, 2, 0) + " ";
	output += getPiece(CORNER, 2, 0);
	output += " ";

	output += getPiece(CORNER, 2, 1) + " ";
	output += getPiece(EDGE, 5, 1) + " ";
	output += getPiece(CORNER, 5, 2);
	output += " ";

	output += getPiece(CORNER, 5, 0) + " ";
	output += getPiece(EDGE, 8, 0) + " ";
	output += getPiece(CORNER, 4, 0);
	output += "\n";

	output += faceOffset + getPiece(CORNER, 3, 1) + " ";
	output += getPiece(EDGE, 2, 1) + " ";
	output += getPiece(CORNER, 2, 2);
	output += "\n";

	output += faceOffset + getPiece(EDGE, 4, 0) + " ";
	output += getColorString('F') + " ";
	output += getPiece(EDGE, 5, 0);
	output += "\n";

	output += faceOffset + getPiece(CORNER, 4, 2) + " ";
	output += getPiece(EDGE, 8, 1) + " ";
	output += getPiece(CORNER, 5, 1);
	output += "\n";

	std::cout << output;
}

void Cube::rotateSide(CubeMove *move) {}

bool CubeMove::isCompatible(CubeMove *move) {
	if (this->side == move->side) {
		return false;
	}

	return true;
}
