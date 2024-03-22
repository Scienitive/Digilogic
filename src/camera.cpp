#include "app.hpp"
#include <raylib.h>
#include <raymath.h>

void App::camera_controls() {
	const float MAX_ZOOM = 3.0f;
	const float MIN_ZOOM = 0.5f;
	const float ZOOM_INCREMENTAL = 0.1f;

	// Panning
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		Vector2 delta = GetMouseDelta();
		delta = Vector2Scale(delta, -1.0f / this->cam.zoom);
		this->cam.target = Vector2Add(this->cam.target, delta);
	}

	// Zooming
	Vector2 mouse_wheel = GetMouseWheelMoveV();
	if (mouse_wheel.y != 0) {
		Vector2 mouse_pos_screen = GetMousePosition();
		Vector2 mouse_pos_world = GetScreenToWorld2D(mouse_pos_screen, this->cam);
		this->cam.offset = mouse_pos_screen;
		this->cam.target = mouse_pos_world;
		this->cam.zoom = Clamp(this->cam.zoom - (mouse_wheel.y * ZOOM_INCREMENTAL), MIN_ZOOM, MAX_ZOOM);
	}
}
