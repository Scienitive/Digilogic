#include "container.hpp"
#include "raylib.h"
#include "ui.hpp"
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

void Container::step() {
	this->set_hovered();

	for (Container *cont : this->children) {
		cont->step();
	}
}

void Container::draw() {
	// Set position and size
	float width = YGNodeLayoutGetWidth(this->node);
	float height = YGNodeLayoutGetHeight(this->node);
	this->set_screen_pos();

	DrawRectangle(this->pos.x, this->pos.y, width, height, this->color);

	for (Container *cont : this->children) {
		cont->draw();
	}
}

void Container::late_step() {
	for (Container *cont : this->children) {
		cont->late_step();
	}
}

void Container::set_hovered() {
	Vector2 cursor_pos = GetMousePosition();
	Vector2 size = {YGNodeLayoutGetWidth(this->node), YGNodeLayoutGetHeight(this->node)};

	if ((cursor_pos.x >= this->pos.x && cursor_pos.x <= this->pos.x + size.x) && cursor_pos.y >= this->pos.y &&
		cursor_pos.y <= this->pos.y + size.y) {
		this->hovered = true;
	} else {
		this->hovered = false;
	}
}

void Container::set_screen_pos() {
	float x = YGNodeLayoutGetLeft(this->node);
	float y = YGNodeLayoutGetTop(this->node);
	YGNode *parent = YGNodeGetParent(this->node);
	while (parent != nullptr) {
		x += YGNodeLayoutGetLeft(parent) + YGNodeLayoutGetMargin(parent, YGEdgeLeft);
		y += YGNodeLayoutGetTop(parent) + YGNodeLayoutGetMargin(parent, YGEdgeTop);
		parent = YGNodeGetParent(parent);
	}
	this->pos = {x, y};
}

void Container::add_child(Container *cont) {
	YGNodeInsertChild(this->node, cont->node, this->children.size());
	this->children.push_back(cont);
}

const std::vector<Container *> Container::get_children() {
	return this->children;
}
