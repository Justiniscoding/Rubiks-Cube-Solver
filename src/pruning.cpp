#include "pruning.h"
#include <fstream>
#include <iostream>

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
		return;
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
