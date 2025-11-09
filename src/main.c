#include <stdio.h>

#include "raylib.h"

int main() {
	const int WindowWidth = 800;
	const int WindowHeight = 450;

	InitWindow(WindowWidth, WindowHeight, "Rubik's Cube Solver");

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Hello World!", 190, 200, 20, LIGHTGRAY);
		EndDrawing();
	}

	return 0;
}
