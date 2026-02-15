#pragma once

void writePruningTable(int *pruningTable, int tableSize, const char *fileName);
void loadPruningTable(const char *fileName, int *table, int tableSize);

long factorial(int n);
long nCr(int n, int r);

void generateThistlethwaiteTables();
