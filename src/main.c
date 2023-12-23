#include "../include/scene/controls.h"
#include "../include/scene/scene.h"
#include <raylib.h>

void update(Scene *app, Controls *controls) {
	input_handler(app, controls);
}

void draw(Scene *app) {
	BeginDrawing();
	ClearBackground(RAYWHITE);
	draw_scene(app);
	EndDrawing();
}

int main(void) {
	// Initial
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 450;
	SetTargetFPS(144);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");
	SetWindowMinSize(800, 450);

	// General Structs
	Scene app = {{0, 0}};
	Controls controls = {false, GetMousePosition()};

	// The Loop
	while (!WindowShouldClose()) {
		update(&app, &controls);
		draw(&app);
	}

	CloseWindow();

	return 0;
}
