#include "../../include/scene/controls.h"
#include "../../include/scene/scene.h"
#include "raylib.h"

static void mouse_movement(Scene *app, Controls *controls) {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !controls->mouse_pressed) {
		controls->mouse_pressed = true;
		controls->mouse.x = GetMouseX();
		controls->mouse.y = GetMouseY();
	} else if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT) && controls->mouse_pressed) {
		controls->mouse_pressed = false;
	}

	if (controls->mouse_pressed) {
		app->pos.x += controls->mouse.x - GetMouseX();
		controls->mouse.x = GetMouseX();
		app->pos.y -= controls->mouse.y - GetMouseY();
		controls->mouse.y = GetMouseY();
	}
}

void input_handler(Scene *app, Controls *controls) { mouse_movement(app, controls); }
