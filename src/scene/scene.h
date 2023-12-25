#ifndef SCENE_H
#define SCENE_H

#include "raylib.h"

typedef struct Cam {
	Vector2 offset;
	Vector2 start_pan;
	Vector2 scale;
} Cam;

typedef struct App {
	Cam cam;
} App;

void draw_scene(App *app);
Vector2 world_to_screen(App *app, Vector2 world);
Vector2 screen_to_world(App *app, Vector2 screen);

#endif
