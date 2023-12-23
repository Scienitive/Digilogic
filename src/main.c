#include "../include/scene/controls.h"
#include "../include/scene/scene.h"
#include <raylib.h>

int main(void) {
	Scene app;
	app.pos.x = 0;
	app.pos.y = 0;
	Controls controls = {false, {GetMouseX(), GetMouseY()}};
	InitWindow(800, 450, "raylib [core] example - basic window");

	while (!WindowShouldClose()) {
		input_handler(&app, &controls);
		BeginDrawing();
		ClearBackground(RAYWHITE);
		draw_scene(&app);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
