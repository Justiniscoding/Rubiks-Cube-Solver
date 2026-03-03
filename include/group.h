#pragma once

#include "cube.h"
#include "helpers.h"
#include "pruning.h"
#include <cstdint>
#include <queue>

class Group {
  public:
	uint8_t *pruningTable;
	int tableSize;
	int startingPosition = 0;

	virtual int encode(Cube *cube) { return 0; };
	virtual void decode(int index, Cube *cube) {};
	virtual bool isSolved(Cube *cube) { return false; };
	virtual bool isMoveAllowed(CubeMove move) { return true; };

	std::string solve(Cube *cube, int tableSize, int depth,
					  std::string solution, CubeSide lastSide) {
		if (depth == 0) {
			if (isSolved(cube)) {
				if (solution == "") {
					return " ";
				}

				return solution.substr(1, solution.length());
			}
		} else if (depth > 0) {
			int index = encode(cube);

			if (pruningTable[index] <= depth) {
				CubeMove move;

				for (int i = 0; i < 18; i++) {
					int side = i % 6;
					int amount = i / 6 + 1;

					move.side = static_cast<CubeSide>(side);

					if (move.side == lastSide) {
						continue;
					}

					if (isMoveAllowed(move) == false) {
						continue;
					}

					move.amount = amount;

					Cube newCube = cube->clone();

					newCube.rotateSide(&move);

					std::string result =
						solve(&newCube, tableSize, depth - 1,
							  solution + " " + move.toString(), move.side);

					if (result != "") {
						return result;
					}
				}
			}
		}
		return "";
	}

	void generatePruningTable(int tableSize, int startingPosition,
							  const char *fileName) {
		Cube cube = Cube::create();

		int distance[tableSize];
		std::queue<int> sq;

		for (int i = 0; i < tableSize; i++) {
			if (i == startingPosition) {
				continue;
			}

			distance[i] = -1;
		}

		distance[startingPosition] = 0;
		sq.push(startingPosition);

		while (!sq.empty()) {
			int num = sq.front();
			sq.pop();

			decode(num, &cube);

			CubeMove move;
			for (int i = 0; i < 18; i++) {
				int side = i % 6;
				int amount = i / 6 + 1;

				move.side = static_cast<CubeSide>(side);
				move.amount = amount;

				if (isMoveAllowed(move) == false) {
					continue;
				}

				Cube newCube = cube.clone();

				newCube.rotateSide(&move);

				int index = encode(&newCube);

				if (distance[index] == -1) {
					distance[index] = distance[num] + 1;
					sq.push(index);
				}
			}
		}

		writePruningTable(distance, tableSize, fileName);
	};

	void loadTable(int tableSize, const char *fileName) {
		pruningTable = new uint8_t[tableSize];
		loadPruningTable(pruningTable, tableSize, fileName);
	}
};
class ThistlethwaiteGroup1 : public Group {
  public:
	int tableSize = 2048;

	int encode(Cube *cube) {
		int t = 0;

		for (int i = 0; i < 11; i++) {
			t *= 2;
			t += cube->edgeOrientation[i];
		}

		return t;
	}

	void decode(int index, Cube *cube) {
		int s = 0;
		for (int i = 10; i >= 0; i--) {
			cube->edgeOrientation[i] = index % 2;
			s -= cube->edgeOrientation[i];
			if (s < 0) {
				s += 2;
			}
			index /= 2;
		}
		cube->edgeOrientation[11] = s;
	}

	bool isSolved(Cube *cube) {
		for (int i = 0; i < 12; i++) {
			if (cube->edgeOrientation[i] != 0) {
				return false;
			}
		}

		return true;
	}

	bool isMoveAllowed(CubeMove move) { return true; }
};

class ThistlethwaiteGroup2 : public Group {
  public:
	int tableSize = 1082565;
	int startingPosition = 69;

	int encode(Cube *cube) {
		int cornerValue = 0;

		for (int i = 0; i < 7; i++) {
			cornerValue *= 3;
			cornerValue += cube->cornerOrientation[i];
		}

		int edgeValue = 0;
		int edgeNumber = 4;

		for (int i = 0; i < 12; i++) {
			int currentEdge = cube->edgePermutation[i];

			if (currentEdge >= 4 && currentEdge <= 7) {
				edgeValue += nCr(11 - i, edgeNumber);
				edgeNumber--;
			}
		}

		return cornerValue * 495 + edgeValue;
	}

	void decode(int index, Cube *cube) {
		int cornerIndex = index / 495;
		int edgeIndex = index % 495;

		int s = 0;

		for (int i = 6; i >= 0; i--) {
			cube->cornerOrientation[i] = cornerIndex % 3;
			s -= cube->cornerOrientation[i];
			if (s < 0) {
				s += 3;
			}
			cornerIndex /= 3;
		}

		cube->cornerOrientation[7] = s;

		int remaining = 4;

		for (int i = 0; i < 12; i++) {
			if (remaining == 0) {
				cube->edgePermutation[i] = 0;
				continue;
			}

			int count = nCr(11 - i, remaining);

			if (edgeIndex < count) {
				cube->edgePermutation[i] = 0;
			} else {
				// Set the edge as a slice edge
				cube->edgePermutation[i] = 4;
				edgeIndex -= count;
				remaining--;
			}
		}
	}

	bool isSolved(Cube *cube) {
		for (int i = 0; i < 4; i++) {
			int permutation = cube->edgePermutation[i + 4];
			if (permutation < 4 || permutation > 7) {
				return false;
			}
		}

		for (int i = 0; i < 8; i++) {
			if (cube->cornerOrientation[i] != 0) {
				return false;
			}
		}

		return true;
	}

	bool isMoveAllowed(CubeMove move) {
		if (move.amount != 2 && (move.side == FRONT || move.side == BACK)) {
			return false;
		}

		return true;
	}
};

class ThistlethwaiteGroup3 : public Group {
  public:
};
