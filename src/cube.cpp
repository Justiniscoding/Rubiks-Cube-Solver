#include "cube.h"
#include "pruning.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
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

Cube Cube::clone() {
	Cube cube;

	for (int i = 0; i < 12; i++) {
		cube.edgeOrientation[i] = edgeOrientation[i];
		cube.edgePermutation[i] = edgePermutation[i];
	}

	for (int i = 0; i < 8; i++) {
		cube.cornerOrientation[i] = cornerOrientation[i];
		cube.cornerPermutation[i] = cornerPermutation[i];
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

void Cube::updateCorner(uint8_t corner, uint8_t newValue) {
	cornerOrientation[corner] = newValue;

	if (cornerOrientation[corner] == 3) {
		cornerOrientation[corner] = 0;
	} else if (cornerOrientation[corner] == 4) {
		cornerOrientation[corner] = 1;
	}
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
	updateCorner(corner1, cornerOrientation[corner2] + num1);
	updateCorner(corner2, cornerOrientation[corner3] + num2);
	updateCorner(corner3, cornerOrientation[corner4] + num1);
	updateCorner(corner4, tempO + num2);
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

	updateCorner(corner1, cornerOrientation[corner2]);
	updateCorner(corner2, tempO);

	updateCorner(corner3, cornerOrientation[corner4]);
	updateCorner(corner4, temp2O);
}

void Cube::cycleEdges(uint8_t edge1, uint8_t edge2, uint8_t edge3,
					  uint8_t edge4) {
	uint8_t temp = edgePermutation[edge1];

	edgePermutation[edge1] = edgePermutation[edge2];
	edgePermutation[edge2] = edgePermutation[edge3];
	edgePermutation[edge3] = edgePermutation[edge4];
	edgePermutation[edge4] = temp;

	uint8_t tempO = edgeOrientation[edge1];

	edgeOrientation[edge1] = edgeOrientation[edge2];
	edgeOrientation[edge2] = edgeOrientation[edge3];
	edgeOrientation[edge3] = edgeOrientation[edge4];
	edgeOrientation[edge4] = tempO;
}

void Cube::updateEdge(uint8_t edge) {
	edgeOrientation[edge]++;

	if (edgeOrientation[edge] == 2) {
		edgeOrientation[edge] = 0;
	}
}

void Cube::cycleEdges(uint8_t edge1, uint8_t edge2, uint8_t edge3,
					  uint8_t edge4, bool flipEdges) {
	cycleEdges(edge1, edge2, edge3, edge4);

	updateEdge(edge1);
	updateEdge(edge2);
	updateEdge(edge3);
	updateEdge(edge4);
}

void Cube::doubleSwapEdges(uint8_t edge1, uint8_t edge2, uint8_t edge3,
						   uint8_t edge4) {
	uint8_t temp = edgePermutation[edge1];
	uint8_t temp2 = edgePermutation[edge3];

	edgePermutation[edge1] = edgePermutation[edge2];
	edgePermutation[edge2] = temp;
	edgePermutation[edge3] = edgePermutation[edge4];
	edgePermutation[edge4] = temp2;

	uint8_t tempO = edgeOrientation[edge1];
	uint8_t temp2O = edgeOrientation[edge3];

	edgeOrientation[edge1] = edgeOrientation[edge2];
	edgeOrientation[edge2] = tempO;

	edgeOrientation[edge3] = edgeOrientation[edge4];
	edgeOrientation[edge4] = temp2O;
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
	} else if (move->side == BACK) {
		if (move->amount == 1) {
			cycleCorners(1, 6, 7, 0, true);
			cycleEdges(0, 6, 10, 7, true);
		} else if (move->amount == 2) {
			doubleSwapCorners(1, 7, 0, 6);
			doubleSwapEdges(0, 10, 6, 7);
		} else if (move->amount == 3) {
			cycleCorners(7, 6, 1, 0, true);
			cycleEdges(10, 6, 0, 7, true);
		}
	} else if (move->side == DOWN) {
		if (move->amount == 1) {
			cycleCorners(4, 7, 6, 5, false);
			cycleEdges(8, 11, 10, 9);
		} else if (move->amount == 2) {
			doubleSwapCorners(4, 6, 7, 5);
			doubleSwapEdges(8, 10, 11, 9);
		} else if (move->amount == 3) {
			cycleCorners(6, 7, 4, 5, false);
			cycleEdges(10, 11, 8, 9);
		}
	}
}

bool CubeMove::isCompatible(CubeMove *move) {
	if (this->side == move->side) {
		return false;
	}

	return true;
}

std::string CubeMove::toString() {
	std::string moveString = "";

	if (side == RIGHT) {
		moveString += "R";
	} else if (side == LEFT) {
		moveString += "L";
	} else if (side == UP) {
		moveString += "U";
	} else if (side == DOWN) {
		moveString += "D";
	} else if (side == FRONT) {
		moveString += "F";
	} else if (side == BACK) {
		moveString += "B";
	}

	if (amount == 2) {
		moveString += "2";
	} else if (amount == 3) {
		moveString += "'";
	}

	return moveString;
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

void Cube::randomScramble() {
	CubeMove lastMove;

	for (int i = 0; i < 20; i++) {
		CubeMove move;
		do {
			move.amount = rand() % 3 + 1;
			move.side = static_cast<CubeSide>(rand() % 6);
		} while (!move.isCompatible(&lastMove));

		lastMove = move;

		rotateSide(&move);
	}
}

std::string Cube::thistlethwaiteGroup1(int *pruningTable, int depth,
									   std::string solution,
									   CubeSide lastSide) {
	if (depth == 0) {
		for (int i = 0; i < 12; i++) {
			if (edgeOrientation[i] != 0) {
				return "";
			}
		}

		if (solution == "") {
			return " ";
		}

		return solution.substr(1, solution.length());
	} else if (depth > 0) {
		int t = 0;

		for (int i = 0; i < 11; i++) {
			t *= 2;
			t += edgeOrientation[i];
		}

		if (pruningTable[t] <= depth) {
			CubeMove move;

			for (int i = 0; i < 18; i++) {
				int side = i % 6;
				int amount = i / 6 + 1;

				// TODO: improve this by using a transition table instead of
				// having to simulate a move for every possible branch. A
				// transition table takes the encoded t value and turns it into
				// a new one without having to create a new cube for every move.
				move.side = static_cast<CubeSide>(side);

				if (move.side == lastSide) {
					continue;
				}

				move.amount = amount;

				Cube newCube = clone();

				newCube.rotateSide(&move);

				std::string result = newCube.thistlethwaiteGroup1(
					pruningTable, depth - 1, solution + " " + move.toString(),
					move.side);

				if (result != "") {
					return result;
				}
			}
		}
	}

	return "";
}

std::string Cube::thistlethwaiteGroup2(int *pruningTable, int depth,
									   std::string solution,
									   CubeSide lastSide) {

	if (depth == 0) {
		for (int i = 0; i < 4; i++) {
			int permutation = edgePermutation[i + 4];
			if (permutation < 4 || permutation > 7) {
				return "";
			}
		}

		for (int i = 0; i < 8; i++) {
			if (cornerOrientation[i] != 0) {
				return "";
			}
		}

		if (solution == "") {
			return " ";
		}

		return solution.substr(1, solution.length());
	} else if (depth > 0) {
		int cornerValue = 0;

		for (int i = 0; i < 7; i++) {
			cornerValue *= 3;
			cornerValue += cornerOrientation[i];
		}

		int edgeValue = 0;
		int edgeNumber = 4;

		for (int i = 0; i < 12; i++) {
			int currentEdge = edgePermutation[i];

			if (currentEdge >= 4 && currentEdge <= 7) {
				edgeValue += nCr(11 - i, edgeNumber);
				edgeNumber--;
			}
		}

		int t = cornerValue * 495 + edgeValue;

		if (pruningTable[t] <= depth) {
			CubeMove move;

			for (int i = 0; i < 18; i++) {
				int side = i % 6;
				int amount = i / 6 + 1;

				move.side = static_cast<CubeSide>(side);
				move.amount = amount;

				// if (move.side == lastSide) {
				// 	continue;
				// }

				if (move.amount != 2 &&
					(move.side == FRONT || move.side == BACK)) {
					continue;
				}

				Cube newCube = clone();

				newCube.rotateSide(&move);

				std::string result = newCube.thistlethwaiteGroup2(
					pruningTable, depth - 1, solution + " " + move.toString(),
					move.side);

				if (result != "") {
					return result;
				}
			}
		}
	}

	return "";
}

// Solve the cube using Thistlethwaite's algorithm.

void Cube::thistlethwaite() {
	int g1[2048];
	loadPruningTable(g1, 2048, "./tables/thistleg1");

	int g2[1082565];
	loadPruningTable(g2, 1082565, "./tables/thistleg2");

	for (int i = 0; i < 7; i++) {
		std::string solution = thistlethwaiteGroup1(g1, i, "", NONE);
		if (solution != "") {
			std::cout << "Solved phase 1 using " << solution << std::endl;
			executeMoves(solution);
			break;
		}
	}

	print();

	for (int i = 0; i < 11; i++) {
		std::string solution = thistlethwaiteGroup2(g2, i, "", NONE);
		if (solution != "") {
			std::cout << "Solved phase 2 using " << solution << std::endl;
			executeMoves(solution);
			break;
		}
	}
}

// Solve the cube using Kociemba's algorithm.
void Cube::kociemba() {}
