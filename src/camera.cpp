#include "camera.hpp"

Cam::Cam() : offset({-GetScreenWidth() / 2.0f, -GetScreenHeight() / 2.0f}), start_pan({0, 0}), scale({1, 1}) {}

Vector2 Cam::world_to_screen(Vector2 world) {
	Vector2 screen = {
		(world.x - this->offset.x) * this->scale.x,
		(-world.y - this->offset.y) * this->scale.y,
	};
	return screen;
}

Vector2 Cam::screen_to_world(Vector2 screen) {
	Vector2 world = {
		screen.x / this->scale.x + this->offset.x,
		// Here could cause some problems because screen.y isnt negative but it works only this way.
		screen.y / this->scale.y + this->offset.y,
	};
	return world;
}

void Cam::draw_component_screen(Vector2 pos, Vector2 size, Color color) {
	DrawRectangle(pos.x - ((size.x * this->scale.x) / 2), pos.y - ((size.y * this->scale.y) / 2),
				  size.x * this->scale.x, size.y * this->scale.y, color);
}

void Cam::draw_component_world(Vector2 pos, Vector2 size, Color color) {
	Vector2 screen_pos = world_to_screen(pos);
	draw_component_screen(screen_pos, size, color);
}

void Cam::panning() {
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		this->start_pan.x = GetMouseX();
		this->start_pan.y = GetMouseY();
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		this->offset.x -= (GetMouseX() - this->start_pan.x) / this->scale.x;
		this->offset.y -= (GetMouseY() - this->start_pan.y) / this->scale.y;
		this->start_pan.x = GetMouseX();
		this->start_pan.y = GetMouseY();
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
	} else {
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	}
}

void Cam::zooming() {
	const float MAX_SCALE = 5.00;
	const float MIN_SCALE = 0.10;
	const float SCALE_RATIO = 0.10;

	Vector2 before_zoom_mouse = this->screen_to_world(GetMousePosition());

	float wheel_movement = GetMouseWheelMoveV().y * SCALE_RATIO;
	this->scale.x -= wheel_movement;
	this->scale.y -= wheel_movement;
	if (this->scale.x > MAX_SCALE) {
		this->scale.x = MAX_SCALE;
	} else if (this->scale.x < MIN_SCALE) {
		this->scale.x = MIN_SCALE;
	}
	if (this->scale.y > MAX_SCALE) {
		this->scale.y = MAX_SCALE;
	} else if (this->scale.y < MIN_SCALE) {
		this->scale.y = MIN_SCALE;
	}

	Vector2 after_zoom_mouse = this->screen_to_world(GetMousePosition());
	this->offset.x += before_zoom_mouse.x - after_zoom_mouse.x;
	this->offset.y += before_zoom_mouse.y - after_zoom_mouse.y;
}

void Cam::input_handler() {
	this->panning();
	this->zooming();
}
