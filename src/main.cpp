#include "scene.hpp"
#include <raylib.h>

void update(App &app) {
	app.input_handler();
	/* check_all_button_hovers(app); */
}

void draw(App &app) {
	BeginDrawing();
	ClearBackground(RAYWHITE);
	app.draw_scene();
	app.draw_ui();
	EndDrawing();
}

int main() {
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 450;
	SetTargetFPS(144);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DigiLogic");
	SetWindowMinSize(800, 450);

	App app;

	while (!WindowShouldClose()) {
		update(app);
		draw(app);
	}

	CloseWindow();

	return 0;
}
