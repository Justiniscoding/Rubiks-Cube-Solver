#pragma once

#include "cube.h"
#include "group.h"
#include <string>

enum SolverMode { THISTLETHWAITE, KOCIEMBA };

struct Solver {
	SolverMode solverMode;

	ThistlethwaiteGroup1 g1;
	ThistlethwaiteGroup2 g2;

	void init(SolverMode solverMode, bool generateTables);
	std::string solveCube(Cube cube);
};
