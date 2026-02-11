#pragma once

#include <stdint.h>
#include <string>

static std::string edges[] = {"UB", "UR", "UF", "UL", "FL", "FR",
							  "BR", "BL", "DF", "DR", "DB", "DL"};

static std::string corners[] = {"ULB", "UBR", "URF", "UFL",
								"DLF", "DFR", "DRB", "DBL"};
enum CubeColor { ORANGE, RED, WHITE, YELLOW, BLUE, GREEN };

enum CubeSide { RIGHT, LEFT, UP, DOWN, BACK, FRONT };

enum PieceType { CORNER, EDGE };

struct CubeMove {
	CubeSide side;
	uint8_t amount;

	bool isCompatible(CubeMove *move);
};

struct Cube {
	uint8_t edgePermutation[12];
	uint8_t edgeOrientation[12];
	uint8_t cornerPermutation[8];
	uint8_t cornerOrientation[8];

	static Cube create();

	std::string getPiece(PieceType type, uint8_t pieceIndex, uint8_t faceIndex);

	void print();
	void rotateSide(CubeMove *move);
};

std::string getColorString(char edge);
