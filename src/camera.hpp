#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <raylib.h>

struct Cam {
	Vector2 offset;
	Vector2 start_pan;
	Vector2 scale;

private:
	void panning();
	void zooming();

public:
	Cam();

	// World position means the position related to the workspace where (0, 0) being the middle of the screen.
	Vector2 world_to_screen(Vector2 world);
	// Screen position means the position related to the program itself where (0, 0) being the top left corner of the
	// screen.
	Vector2 screen_to_world(Vector2 screen);

	void draw_component_screen(Vector2 pos, Vector2 size, Color color);
	void draw_component_world(Vector2 pos, Vector2 size, Color color);

	void input_handler();
};

#endif
