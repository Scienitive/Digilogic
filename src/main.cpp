#include "app.hpp"
#include <iostream>
#include <raylib.h>
#include <yoga/YGNodeStyle.h>
#include <yoga/Yoga.h>

int main() {
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 450;
	SetTargetFPS(60);
	SetExitKey(0);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DigiLogic");
	SetWindowMinSize(800, 450);

	App &app = App::get();

	while (!WindowShouldClose()) {
		// Step
		app.step();

		// Draw
		BeginDrawing();
		ClearBackground(WHITE);
		app.draw();
		EndDrawing();

		// Late Step
		app.late_step();

		if (app.states.exit) {
			break;
		}
	}

	return 0;
}
