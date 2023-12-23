#ifndef CONTROLS_H
#define CONTROLS_H

#include "raylib.h"
#include "scene.h"
#include <stdbool.h>

typedef struct Controls {
	bool mouse_pressed;
	Vector2 mouse;
} Controls;

void input_handler(Scene *app, Controls *controls);

#endif
