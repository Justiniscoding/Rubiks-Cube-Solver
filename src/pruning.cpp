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

	std::cout << "Successfully wrote to pruning table!\n";
}

void loadPruningTable(const char *fileName, int *table, int tableSize) {
	std::ifstream file(fileName);

	if (!file.is_open()) {
		std::cout << "Error while opening pruning table!\n";
	}

	char character;

	std::string key = "";
	std::string value = "";

	int stage = 0;

	// int table[tableSize];

	while (file.get(character)) {
		if (stage == 0) {
			if (character == ',') {
				stage++;
			} else {
				key += character;
			}
		} else {
			if (character == ';') {
				// std::cout << "The string ofr the key is " << key
				// 		  << " and the string for the value is " << value
				// 		  << "\n";
				stage = 0;
				table[std::stoi(key)] = std::stoi(value);
				key = "";
				value = "";
			} else {
				value += character;
			}
		}
	}
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
			int amount = i / 6;
			move.side = static_cast<CubeSide>(side);
			move.amount = amount;

			cube.rotateSide(&move);

			int t = 0;

			for (int i = 0; i < 11; i++) {
				t *= 2;
				t += cube.edgeOrientation[i];
			}

			if (distance[t] == -1) {
				distance[t] = lastDist + 1;
				sq.push(t);
			}

			move.amount = 4 - move.amount;
			cube.rotateSide(&move);
		}
	}

	writePruningTable(distance, 2048, "./tables/thistleg1");
}
