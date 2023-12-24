#include "scene.h"
#include <raylib.h>

void draw_scene(Scene *app) {
	Vector2 obj1;
	Vector2 obj2;

	obj1.x = 0;
	obj1.y = 0;

	obj2.x = -140;
	obj2.y = 140;

	int midpoint_x = GetScreenWidth() / 2;
	int midpoint_y = GetScreenHeight() / 2;
	DrawRectangle(midpoint_x + (obj1.x - app->pos.x) - 50, midpoint_y + (app->pos.y - obj1.y) - 50, 100, 100, GREEN);
	DrawRectangle(midpoint_x + (obj2.x - app->pos.x) - 50, midpoint_y + (app->pos.y - obj2.y) - 50, 100, 100, GREEN);
}
