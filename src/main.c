#include <stdio.h>

/* #include "raylib.h" */

#include "cube.h"

Cube RubiksCube;

void setup() {
	RubiksCube = CreateCube("WWWWWWWWBBBBBBBBOOOOOOOOGGGGGGGGRRRRRRRRYYYYYYYY");

	const int windowWidth = 800;
	const int windowHeight = 450;

	/* InitWindow(windowWidth, windowHeight, "Rubik's Cube Solver"); */
	/**/
	/* SetTargetFPS(60); */
}

int main() {
	setup();

	/* while (!WindowShouldClose()) { */
	/* 	BeginDrawing(); */
	/* 	ClearBackground(RAYWHITE); */
	/* 	DrawText("Hello World!", 190, 200, 20, LIGHTGRAY); */
	/* 	EndDrawing(); */
	/* } */

	return 0;
}
