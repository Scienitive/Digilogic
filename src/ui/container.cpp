#include "container.hpp"
#include "raylib.h"
#include "yoga/YGNode.h"
#include "yoga/YGNodeLayout.h"

Container::Container() : color(BLANK) {
	this->node = YGNodeNew();
}

Container::~Container() {
	for (Container *cont : this->children) {
		delete cont;
	}
}

void Container::draw() {
	float width = YGNodeLayoutGetWidth(this->node);
	float height = YGNodeLayoutGetHeight(this->node);

	Vector2 pos = this->get_screen_pos();
	DrawRectangle(pos.x, pos.y, width, height, this->color);

	for (Container *cont : this->children) {
		cont->draw();
	}
}

Vector2 Container::get_screen_pos() {
	float x = YGNodeLayoutGetLeft(this->node);
	float y = YGNodeLayoutGetTop(this->node);
	YGNode *parent = YGNodeGetParent(this->node);
	while (parent != nullptr) {
		x += YGNodeLayoutGetLeft(parent) + YGNodeLayoutGetMargin(parent, YGEdgeLeft);
		y += YGNodeLayoutGetTop(parent) + YGNodeLayoutGetMargin(parent, YGEdgeTop);
		parent = YGNodeGetParent(parent);
	}
	return {x, y};
}

void Container::add_child(Container *cont) {
	YGNodeInsertChild(this->node, cont->node, this->children.size());
	this->children.push_back(cont);
}

const std::vector<Container *> Container::get_children() {
	return this->children;
}
