#include "ui/ui.hpp"
#include <iostream>
#include <raylib.h>
#include <yoga/YGNodeStyle.h>
#include <yoga/Yoga.h>

int main() {
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 450;
	SetTargetFPS(60);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DigiLogic");
	SetWindowMinSize(800, 450);

	UI ui = UI();

	while (!WindowShouldClose()) {
		// Step
		ui.step();

		// Draw
		BeginDrawing();
		ClearBackground(WHITE);
		ui.draw();
		EndDrawing();

		// Late Step
		ui.late_step();
	}

	return 0;
}
