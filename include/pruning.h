#pragma once

void writePruningTable(int *pruningTable, int tableSize, const char *fileName);

void generateThistlethwaiteTables();
void loadPruningTable(const char *fileName, int *table, int tableSize);
