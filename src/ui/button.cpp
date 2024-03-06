#include "button.hpp"
#include "container.hpp"
#include "textlabel.hpp"
#include "yoga/YGNodeStyle.h"
#include <yoga/Yoga.h>

Button::Button(std::string text) {
	this->text_label = new TextLabel(text);
	YGNodeStyleSetPaddingPercent(this->node, YGEdgeAll, 2);
	YGNodeStyleSetHeightPercent(this->node, 100);
	YGNodeInsertChild(this->node, this->text_label->node, 0);
}

Button::~Button() {
	delete text_label;
}

void Button::draw() {
	Container::draw();
	text_label->draw();
}
