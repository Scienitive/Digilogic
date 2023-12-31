#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include "scene.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct App App;

typedef struct Button {
	Vector2 positon;
	char *text;
	int height;
	bool hovered;
	Color color;
} Button;

void initialize_buttons(App *app);
size_t get_button_width(Button *button);
void draw_button(Button *button);
void check_all_button_hovers(App *app);

#endif
