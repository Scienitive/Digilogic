#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <raylib.h>

class Object {
	Vector2 pos;
	Vector2 size;

public:
	Object();
	Object(Vector2 pos, Vector2 size);
};

#endif
