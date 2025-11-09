# Rubik's Cube Solver

This program implements a Rubik's cube solver using [Kociemba's algorithm](https://www.speedsolving.com/wiki/index.php/Kociemba%27s_Algorithm). It also features a Rubik's cube simulator powered by [raylib](https://github.com/raysan5/raylib)

Kociemba's algorithm is a fast Rubik's cube solving algorithm that generates near-optimal solutions using a two phase algorithm. The algorithm first reduces the cube to the "Domino Phase," where it becomes solvable using only the <U, D, F2, B2, R2, L2> move set. 
