#include "pruning.h"
#include <cstdint>
#include <fstream>
#include <iostream>

void writePruningTable(int *pruningTable, int tableSize, const char *fileName) {
	std::ofstream file(fileName, std::ios::out | std::ios::binary);

	if (!file.is_open()) {
		std::cout << "Error while opening pruning table!\n";
		return;
	}

	for (int i = 0; i < tableSize; i++) {
		int value = pruningTable[i];

		file.write((char *)&pruningTable[i], 4);
	}

	file.close();

	std::cout << "Successfully wrote to pruning table at " << fileName << "!"
			  << std::endl;
}

void loadPruningTable(uint8_t *table, int tableSize, const char *fileName) {
	std::ifstream file(fileName, std::ios::in | std::ios::binary);

	if (!file.is_open()) {
		std::cout << "Error while opening pruning table!\n";
		return;
	}

	for (int i = 0; i < tableSize; i++) {
		file.read((char *)&table[i], 4);
	}

	std::cout << "Successfully loaded pruning table at " << fileName << "!"
			  << std::endl;
}
