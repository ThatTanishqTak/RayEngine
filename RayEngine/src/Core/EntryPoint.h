#pragma once

#include <raylib.h>

int main()
{
	InitWindow(800, 600, "RayEngine");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}