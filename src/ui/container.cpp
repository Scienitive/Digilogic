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
	float x = YGNodeLayoutGetLeft(this->node);
	float y = YGNodeLayoutGetTop(this->node);
	DrawRectangle(x, y, width, height, this->color);

	for (Container *cont : this->children) {
		cont->draw();
	}
}

void Container::add_child(Container *cont) {
	YGNodeInsertChild(this->node, cont->node, this->children.size());
	this->children.push_back(cont);
}
