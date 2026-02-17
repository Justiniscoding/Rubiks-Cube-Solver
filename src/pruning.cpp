#include "pruning.h"
#include "cube.h"
#include <fstream>
#include <iostream>
#include <queue>

void writePruningTable(int *pruningTable, int tableSize, const char *fileName) {
	std::ofstream file(fileName);

	if (!file.is_open()) {
		std::cout << "Error while opening pruning table!\n";
		return;
	}

	for (int i = 0; i < tableSize; i++) {
		int value = pruningTable[i];

		file << i << "," << value << ";";
	}

	file.close();

	std::cout << "Successfully wrote to pruning table at " << fileName << "!"
			  << std::endl;
}

void loadPruningTable(int *table, int tableSize, const char *fileName) {
	std::ifstream file(fileName);

	if (!file.is_open()) {
		std::cout << "Error while opening pruning table!\n";
	}

	char character;

	std::string key = "";
	std::string value = "";

	int stage = 0;

	while (file.get(character)) {
		if (stage == 0) {
			if (character == ',') {
				stage++;
			} else {
				key += character;
			}
		} else {
			if (character == ';') {
				stage = 0;
				table[std::stoi(key)] = std::stoi(value);
				key = "";
				value = "";
			} else {
				value += character;
			}
		}
	}

	std::cout << "Successfully loaded pruning table at " << fileName << "!"
			  << std::endl;
}

long factorial(int n) {
	long result = 1;

	for (int i = 2; i <= n; i++) {
		result *= i;
	}

	return result;
}

long nCr(int n, int r) {
	return factorial(n) / (factorial(r) * factorial(n - r));
}

void generateThistlethwaiteTables() {
	Cube cube = Cube::create();

	int distance[2048];
	std::queue<int> sq;

	for (int i = 1; i < 2048; i++) {
		distance[i] = -1;
	}

	sq.push(0);
	distance[0] = 0;

	while (!sq.empty()) {
		int num = sq.front();
		int element = num;
		sq.pop();

		int s = 0;
		for (int i = 10; i >= 0; i--) {
			cube.edgeOrientation[i] = num % 2;
			s -= cube.edgeOrientation[i];
			if (s < 0) {
				s += 2;
			}
			num /= 2;
		}
		cube.edgeOrientation[11] = s;

		int lastDist = distance[element];

		CubeMove move;
		for (int i = 0; i < 18; i++) {
			int side = i % 6;
			int amount = i / 6 + 1;

			move.side = static_cast<CubeSide>(side);
			move.amount = amount;

			Cube newCube = cube.clone();

			newCube.rotateSide(&move);

			int t = 0;

			for (int i = 0; i < 11; i++) {
				t *= 2;
				t += newCube.edgeOrientation[i];
			}

			if (distance[t] == -1) {
				distance[t] = lastDist + 1;
				sq.push(t);
			}
		}
	}

	writePruningTable(distance, 2048, "./tables/thistleg1");

	cube = Cube::create();

	int g2Distance[1082565];

	for (int i = 0; i < 1082565; i++) {
		g2Distance[i] = -1;
	}

	// 69 represents a cube with full oriented corners and edges in the e slice
	g2Distance[69] = 0;
	sq.push(69);

	while (!sq.empty()) {
		int num = sq.front();
		sq.pop();

		int lastDist = g2Distance[num];

		int cornerIndex = num / 495;
		int edgeIndex = num % 495;

		int s = 0;

		for (int i = 6; i >= 0; i--) {
			cube.cornerOrientation[i] = cornerIndex % 3;
			s -= cube.cornerOrientation[i];
			if (s < 0) {
				s += 3;
			}
			cornerIndex /= 3;
		}
		cube.cornerOrientation[7] = s;

		int remaining = 4;

		for (int i = 0; i < 12; i++) {
			if (remaining == 0) {
				cube.edgePermutation[i] = 0;
				continue;
			}

			int count = nCr(11 - i, remaining);

			if (edgeIndex < count) {
				cube.edgePermutation[i] = 0;
			} else {
				// Set the edge as a slice edge
				cube.edgePermutation[i] = 4;
				edgeIndex -= count;
				remaining--;
			}
		}

		CubeMove move;
		for (int i = 0; i < 18; i++) {
			int side = i % 6;
			int amount = i / 6 + 1;

			move.side = static_cast<CubeSide>(side);
			move.amount = amount;

			if (move.amount != 2 && (move.side == FRONT || move.side == BACK)) {
				continue;
			}

			Cube newCube = cube.clone();

			newCube.rotateSide(&move);

			int cornerValue = 0;

			for (int i = 0; i < 7; i++) {
				cornerValue *= 3;
				cornerValue += newCube.cornerOrientation[i];
			}

			int edgeValue = 0;
			int edgeNumber = 4;

			for (int i = 0; i < 12; i++) {
				int currentEdge = newCube.edgePermutation[i];

				if (currentEdge >= 4 && currentEdge <= 7) {
					edgeValue += nCr(11 - i, edgeNumber);
					edgeNumber--;
				}
			}

			int t = cornerValue * 495 + edgeValue;

			if (g2Distance[t] == -1) {
				g2Distance[t] = lastDist + 1;
				sq.push(t);
			}
		}
	}

	writePruningTable(g2Distance, 1082565, "./tables/thistleg2");
}
