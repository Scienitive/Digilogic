#include "scene.h"
#include "button.h"
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>

Vector2 world_to_screen(App *app, Vector2 world) {
	Vector2 screen = {
		(world.x - app->cam.offset.x) * app->cam.scale.x,
		(-world.y - app->cam.offset.y) * app->cam.scale.y,
	};
	return screen;
}

Vector2 screen_to_world(App *app, Vector2 screen) {
	Vector2 world = {
		screen.x / app->cam.scale.x + app->cam.offset.x,
		// Here could cause some problems because screen.y isnt negative but it works only this way.
		screen.y / app->cam.scale.y + app->cam.offset.y,
	};
	return world;
}

void draw_scene(App *app) {
	Vector2 obj1;
	Vector2 obj2;

	obj1.x = 0;
	obj1.y = 0;

	obj2.x = -140;
	obj2.y = 140;

	Vector2 screen_obj1 = world_to_screen(app, obj1);
	Vector2 screen_obj2 = world_to_screen(app, obj2);

	DrawRectangle(screen_obj1.x - ((100 * app->cam.scale.x) / 2), screen_obj1.y - ((100 * app->cam.scale.y) / 2),
				  100 * app->cam.scale.x, 100 * app->cam.scale.y, GREEN);
	DrawRectangle(screen_obj2.x - ((100 * app->cam.scale.x) / 2), screen_obj2.y - ((100 * app->cam.scale.y) / 2),
				  100 * app->cam.scale.x, 100 * app->cam.scale.y, GREEN);
}

void draw_ui(App *app) {
	const int MAX_UI_HEIGHT = 64;
	const int MIN_UI_HEIGHT = 32;

	int ui_height = GetScreenHeight() / 12;
	if (ui_height > MAX_UI_HEIGHT) {
		ui_height = MAX_UI_HEIGHT;
	} else if (ui_height < MIN_UI_HEIGHT) {
		ui_height = MIN_UI_HEIGHT;
	}

	const int SIDE_MARGIN = 16;
	const int BUTTON_GAP = 16;
	const float BUTTON_HEIGHT_RATIO = 0.8;
	// Top
	DrawRectangle(0, 0, GetScreenWidth(), ui_height, YELLOW);

	// Top Left Buttons
	for (size_t i = 0; i < app->buttons.top_left.size; i++) {
		Button *button = (Button *)at_array(&app->buttons.top_left, i);
		button->height = ui_height * BUTTON_HEIGHT_RATIO;

		int distance = 0;
		if (i != 0) {
			for (int j = i - 1; j >= 0; j--) {
				Button *prev_button = (Button *)at_array(&app->buttons.top_left, j);
				distance += get_button_width(prev_button) + BUTTON_GAP;
			}
		}
		Vector2 pos = {
			SIDE_MARGIN + distance,
			(float)(ui_height - button->height) / 2.0,
		};
		button->positon = pos;
		draw_button(button);
	}

	// Top Right Buttons
	for (size_t i = 0; i < app->buttons.top_right.size; i++) {
		Button *button = (Button *)at_array(&app->buttons.top_right, i);
		button->height = ui_height * BUTTON_HEIGHT_RATIO;

		int distance = 0;
		if (i != 0) {
			for (int j = i - 1; j >= 0; j--) {
				Button *prev_button = (Button *)at_array(&app->buttons.top_right, j);
				distance += get_button_width(prev_button) + BUTTON_GAP;
			}
		}
		Vector2 pos = {
			GetScreenWidth() - get_button_width(button) - (SIDE_MARGIN + distance),
			(float)(ui_height - button->height) / 2.0,
		};
		button->positon = pos;
		draw_button(button);
	}

	// Bottom
	DrawRectangle(0, GetScreenHeight() - ui_height, GetScreenWidth(), ui_height, YELLOW);
}

void free_app(App *app) {
	free_array(&app->buttons.top_left);
	free_array(&app->buttons.top_right);
}
