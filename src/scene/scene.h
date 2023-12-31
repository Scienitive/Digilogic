#ifndef SCENE_H
#define SCENE_H

#include "../lib/array.h"
#include "button.h"
#include "raylib.h"

typedef struct Button Button;

typedef struct ButtonGroups {
	Array top_left;
	Array top_right;
} ButtonGroups;

typedef struct Cam {
	Vector2 offset;
	Vector2 start_pan;
	Vector2 scale;
} Cam;

typedef struct App {
	Cam cam;
	ButtonGroups buttons;
} App;

void draw_scene(App *app);
Vector2 world_to_screen(App *app, Vector2 world);
Vector2 screen_to_world(App *app, Vector2 screen);
void draw_ui(App *app);
void free_app(App *app);

#endif
