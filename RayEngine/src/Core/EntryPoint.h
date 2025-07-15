#pragma once

#include "raylib.h"

int main()
{
	InitWindow(1920, 1080, "RayEngine");
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