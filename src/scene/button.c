#include "button.h"
#include "../lib/array.h"
#include "raylib.h"
#include "scene.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FONT_MULTIPLIER 0.9
#define FONT_SPACING 1.5
#define BUTTON_WIDTH_MULTIPLIER 1.2

size_t get_button_width(Button *button) {
	int font_size = button->height * FONT_MULTIPLIER;
	Vector2 text_dimensions = MeasureTextEx(GetFontDefault(), button->text, font_size, FONT_SPACING);
	return (text_dimensions.x * BUTTON_WIDTH_MULTIPLIER);
}

static void button_hover_check(Button *button) {
	Vector2 mouse_position = GetMousePosition();
	if (mouse_position.x >= button->positon.x && mouse_position.x <= button->positon.x + get_button_width(button) &&
		mouse_position.y >= button->positon.y && mouse_position.y <= button->positon.y + button->height) {
		button->hovered = true;
	} else {
		button->hovered = false;
	}
}

void check_all_button_hovers(App *app) {
	for (size_t i = 0; i < app->buttons.top_left.size; i++) {
		Button *button = (Button *)at_array(&app->buttons.top_left, i);
		button_hover_check(button);
	}

	for (size_t i = 0; i < app->buttons.top_right.size; i++) {
		Button *button = (Button *)at_array(&app->buttons.top_right, i);
		button_hover_check(button);
	}
}

void draw_button(Button *button) {
	Vector2 size = {
		get_button_width(button),
		button->height,
	};

	Color color;
	if (button->hovered) {
		color = ColorBrightness(button->color, -1);
	} else {
		color = button->color;
	}

	DrawRectangle(button->positon.x, button->positon.y, size.x, size.y, color);

	int font_size = button->height * FONT_MULTIPLIER;
	Vector2 text_dimensions = MeasureTextEx(GetFontDefault(), button->text, font_size, FONT_SPACING);
	Vector2 text_pos = {
		button->positon.x + (text_dimensions.x * (BUTTON_WIDTH_MULTIPLIER - 1) / 2),
		button->positon.y + (button->height - text_dimensions.y),
	};
	DrawTextEx(GetFontDefault(), button->text, text_pos, font_size, FONT_SPACING, BLACK);
}

void initialize_buttons(App *app) {
	Button exit_button = {
		.text = "EXIT",
		.color = PURPLE,
		.hovered = false,
	};
	Button settings_button = {
		.text = "SETTINGS",
		.color = PURPLE,
		.hovered = false,
	};
	Button github_button = {
		.text = "GITHUB",
		.color = PURPLE,
		.hovered = false,
	};

	init_array(&app->buttons.top_left, sizeof(Button));
	init_array(&app->buttons.top_right, sizeof(Button));

	push_array(&app->buttons.top_left, &github_button);
	push_array(&app->buttons.top_right, &exit_button);
	push_array(&app->buttons.top_right, &settings_button);
}
