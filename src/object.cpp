#include "object.hpp"
#include "raylib.h"

Object::Object() : world_pos({0, 0}), width(100), height(100), color(RED) {}

Object::~Object() {}

void Object::draw() {
	Vector2 modified_world_pos = {this->world_pos.x - this->width / 2, this->world_pos.y - this->height / 2};
	DrawRectangleV(modified_world_pos, {this->width, this->height}, this->color);
}
