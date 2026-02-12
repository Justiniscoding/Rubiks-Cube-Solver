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

void Cube::cycleCorners(uint8_t corner1, uint8_t corner2, uint8_t corner3,
						uint8_t corner4, bool rotateFaces) {
	uint8_t temp = cornerPermutation[corner1];

	cornerPermutation[corner1] = cornerPermutation[corner2];
	cornerPermutation[corner2] = cornerPermutation[corner3];
	cornerPermutation[corner3] = cornerPermutation[corner4];
	cornerPermutation[corner4] = temp;

	int num1 = 1;
	int num2 = 2;

	if (!rotateFaces) {
		num1 = 0;
		num2 = 0;
	}

	uint8_t tempO = cornerOrientation[corner1];
	cornerOrientation[corner1] = cornerOrientation[corner2] + num1;
	cornerOrientation[corner2] = cornerOrientation[corner3] + num2;
	cornerOrientation[corner3] = cornerOrientation[corner4] + num1;
	cornerOrientation[corner4] = tempO + num2;
}

void Cube::doubleSwapCorners(uint8_t corner1, uint8_t corner2, uint8_t corner3,
							 uint8_t corner4) {
	uint8_t temp = cornerPermutation[corner1];
	uint8_t temp2 = cornerPermutation[corner3];

	cornerPermutation[corner1] = cornerPermutation[corner2];
	cornerPermutation[corner2] = temp;
	cornerPermutation[corner3] = cornerPermutation[corner4];
	cornerPermutation[corner4] = temp2;

	uint8_t tempO = cornerOrientation[corner1];
	uint8_t temp2O = cornerOrientation[corner3];

	cornerOrientation[corner1] = cornerOrientation[corner2];
	cornerOrientation[corner2] = tempO;

	cornerOrientation[corner3] = cornerOrientation[corner4];
	cornerOrientation[corner4] = temp2O;
}

void Cube::cycleEdges(uint8_t edge1, uint8_t edge2, uint8_t edge3,
					  uint8_t edge4) {
	uint8_t temp = edgePermutation[edge1];

	edgePermutation[edge1] = edgePermutation[edge2];
	edgePermutation[edge2] = edgePermutation[edge3];
	edgePermutation[edge3] = edgePermutation[edge4];
	edgePermutation[edge4] = temp;
}

void Cube::cycleEdges(uint8_t edge1, uint8_t edge2, uint8_t edge3,
					  uint8_t edge4, bool flipEdges) {
	cycleEdges(edge1, edge2, edge3, edge4);

	edgeOrientation[edge1]++;
	edgeOrientation[edge2]++;
	edgeOrientation[edge3]++;
	edgeOrientation[edge4]++;
}

void Cube::doubleSwapEdges(uint8_t edge1, uint8_t edge2, uint8_t edge3,
						   uint8_t edge4) {
	uint8_t temp = edgePermutation[edge1];
	uint8_t temp2 = edgePermutation[edge3];

	edgePermutation[edge1] = edgePermutation[edge2];
	edgePermutation[edge2] = temp;
	edgePermutation[edge3] = edgePermutation[edge4];
	edgePermutation[edge4] = temp2;
}

void Cube::rotateSide(CubeMove *move) {
	if (move->side == RIGHT) {
		if (move->amount == 1) {
			cycleCorners(6, 1, 2, 5, true);
			cycleEdges(9, 6, 1, 5);
		} else if (move->amount == 2) {
			doubleSwapCorners(2, 6, 1, 5);
			doubleSwapEdges(1, 9, 6, 5);
		} else if (move->amount == 3) {
			cycleCorners(2, 1, 6, 5, true);
			cycleEdges(9, 5, 1, 6);
		}
	} else if (move->side == LEFT) {
		if (move->amount == 1) {
			cycleCorners(4, 3, 0, 7, true);
			cycleEdges(11, 4, 3, 7);
		} else if (move->amount == 2) {
			doubleSwapCorners(0, 4, 3, 7);
			doubleSwapEdges(3, 11, 4, 7);
		} else if (move->amount == 3) {
			cycleCorners(4, 7, 0, 3, true);
			cycleEdges(3, 4, 11, 7);
		}
	} else if (move->side == UP) {
		if (move->amount == 1) {
			cycleCorners(1, 0, 3, 2, false);
			cycleEdges(1, 0, 3, 2);
		} else if (move->amount == 2) {
			doubleSwapEdges(0, 2, 1, 3);
			doubleSwapCorners(0, 2, 1, 3);
		} else if (move->amount == 3) {
			cycleCorners(1, 2, 3, 0, false);
			cycleEdges(1, 2, 3, 0);
		}
	} else if (move->side == FRONT) {
		if (move->amount == 1) {
			cycleCorners(3, 4, 5, 2, true);
			cycleEdges(2, 4, 8, 5, true);
		} else if (move->amount == 2) {
			doubleSwapCorners(3, 5, 4, 2);
			doubleSwapEdges(2, 8, 4, 5);
		} else if (move->amount == 3) {
			cycleCorners(5, 4, 3, 2, true);
			cycleEdges(8, 4, 2, 5, true);
		}
	}
}

bool CubeMove::isCompatible(CubeMove *move) {
	if (this->side == move->side) {
		return false;
	}

	return true;
}

void Cube::executeMoves(std::string moves) {
	CubeMove move;

	for (int i = 0; i < moves.length(); i++) {
		char s = moves[i];

		if (s == 'R') {
			move.side = RIGHT;
		} else if (s == 'L') {
			move.side = LEFT;
		} else if (s == 'F') {
			move.side = FRONT;
		} else if (s == 'B') {
			move.side = BACK;
		} else if (s == 'D') {
			move.side = DOWN;
		} else if (s == 'U') {
			move.side = UP;
		}

		if (s == '2') {
			move.amount = 2;
		}
		if (s == '\'') {
			move.amount = 3;
		}

		if (s == ' ' || i == moves.length() - 1) {
			rotateSide(&move);
			move.amount = 1;
		}
	}
}
