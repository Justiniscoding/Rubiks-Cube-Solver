#include "pruning.h"
#include "cube.h"
#include <fstream>
#include <iostream>
#include <queue>

void writePruningTable(int *pruningTable, const char *fileName) {
	std::ofstream file(fileName);

	if (!file.is_open()) {
		std::cout << "Error while opening pruning table!\n";
		return;
	}

	file << "hello world!";

	file.close();

	std::cout << "Successfully wrote to pruning table!\n";
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
		int element = sq.front();
		sq.pop();

		int s = 0;
		for (int i = 10; i >= 0; i--) {
			cube.edgeOrientation[i] = element % 2;
			s -= cube.edgeOrientation[i];
			if (s < 0) {
				s += 2;
			}
			element /= 2;
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
				std::cout << "The distance to " << t << " is " << distance[t]
						  << "\n";
				sq.push(t);
			}

			move.amount = 4 - move.amount;
			cube.rotateSide(&move);
		}
	}

	int t = 0;

	for (int i = 0; i < 11; i++) {
		t *= 2;
		t += cube.edgeOrientation[i];
	}

	std::cout << "The encoded edge orientation is " << t;

	// int explored[2048];
}
