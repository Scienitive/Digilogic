#include "scene.h"
#include <raylib.h>

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
