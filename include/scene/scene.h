#ifndef SCENE_H
#define SCENE_H

#include "raylib.h"

typedef struct Scene {
	Vector2 pos;
} Scene;

void draw_scene(Scene *app);

#endif
