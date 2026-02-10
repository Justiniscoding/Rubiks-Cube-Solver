#pragma once

#include <stdint.h>
#include <string>

static std::string edges[] = {};
static std::string corners[] = {"ULB", "UBR", "URF", "UFB",
								"DLF", "DFR", "DRB", "DBL"};

struct Cube {
	uint8_t edgePermutation[8];
	uint8_t edgeOrientation[8];
	uint8_t cornerPermutation[12];
	uint8_t cornerOrientation[12];

	static Cube create();

	void print();
};

enum CubeSide { RIGHT, LEFT, UP, DOWN, BACK, FRONT };

struct CubeMove {
	CubeSide side;
	uint8_t amount;

	bool isCompatible(CubeMove *move);
};
