#include "solver.h"
#include <cstdlib>
#include <iostream>

void Solver::init(SolverMode solverMode, bool generateTables) {
	this->solverMode = solverMode;

	if (solverMode == THISTLETHWAITE) {
		if (generateTables) {
			g1.generatePruningTable(2048, 0, "./tables/thistleg1");
			g2.generatePruningTable(1082565, 69, "./tables/thistleg2");
		}

		g1.loadTable(2048, "./tables/thistleg1");
		g2.loadTable(1082565, "./tables/thistleg2");
	}

	std::cout << "Cube solver successfully initialized!" << std::endl;
}

std::string Solver::solveCube(Cube cube) {
	std::string fullSolution = "";

	if (solverMode == THISTLETHWAITE) {
		for (int i = 0; i < 7; i++) {
			std::string solution = g1.solve(&cube, 2048, i, "", NONE);
			if (solution != "") {
				std::cout << "Solved phase 1 using " << solution << std::endl;
				cube.executeMoves(solution);
				fullSolution += solution;
				break;
			}
		}

		cube.print();

		for (int i = 0; i < 10; i++) {
			std::string solution = g2.solve(&cube, 1082565, i, "", NONE);
			if (solution != "") {
				std::cout << "Solved phase 2 using " << solution << std::endl;
				cube.executeMoves(solution);
				fullSolution += solution;
				break;
			}
		}

		cube.print();
	}

	return fullSolution;
}
