#include "scene/controls.h"
#include "scene/scene.h"
#include <raylib.h>

void update(App *app) {
	input_handler(app);
}

void draw(App *app) {
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
	App app = {
		.cam =
			{
				.scale = {1, 1},
				.offset = {-GetScreenWidth() / 2.0, -GetScreenHeight() / 2.0},
				.start_pan = {0, 0},
			},
	};

	// The Loop
	while (!WindowShouldClose()) {
		update(&app);
		draw(&app);
	}

	CloseWindow();

	return 0;
}
