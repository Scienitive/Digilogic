#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <raylib.h>

struct Object {
	Vector2 world_pos;
	float width;
	float height;
	Color color;

	Object();
	~Object();

	void draw();
};

#endif
