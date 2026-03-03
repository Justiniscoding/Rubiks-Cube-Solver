#pragma once

#include <cstdint>

void writePruningTable(int *pruningTable, int tableSize, const char *fileName);
void loadPruningTable(uint8_t *table, int tableSize, const char *fileName);
