#include "controls.h"
#include "scene.h"
#include <raylib.h>

static void panning(App *app) {
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		app->cam.start_pan.x = GetMouseX();
		app->cam.start_pan.y = GetMouseY();
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		app->cam.offset.x -= (GetMouseX() - app->cam.start_pan.x) / app->cam.scale.x;
		app->cam.offset.y -= (GetMouseY() - app->cam.start_pan.y) / app->cam.scale.y;
		app->cam.start_pan.x = GetMouseX();
		app->cam.start_pan.y = GetMouseY();
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
	} else {
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	}
}

static void zooming(App *app) {
	const float MAX_SCALE = 5.00;
	const float MIN_SCALE = 0.10;
	const float SCALE_RATIO = 0.10;

	Vector2 before_zoom_mouse = screen_to_world(app, GetMousePosition());

	float wheel_movement = GetMouseWheelMoveV().y * SCALE_RATIO;
	app->cam.scale.x -= wheel_movement;
	app->cam.scale.y -= wheel_movement;
	if (app->cam.scale.x > MAX_SCALE) {
		app->cam.scale.x = MAX_SCALE;
	} else if (app->cam.scale.x < MIN_SCALE) {
		app->cam.scale.x = MIN_SCALE;
	}
	if (app->cam.scale.y > MAX_SCALE) {
		app->cam.scale.y = MAX_SCALE;
	} else if (app->cam.scale.y < MIN_SCALE) {
		app->cam.scale.y = MIN_SCALE;
	}

	Vector2 after_zoom_mouse = screen_to_world(app, GetMousePosition());
	app->cam.offset.x += before_zoom_mouse.x - after_zoom_mouse.x;
	app->cam.offset.y += before_zoom_mouse.y - after_zoom_mouse.y;
}

void input_handler(App *app) {
	panning(app);
	zooming(app);
}
