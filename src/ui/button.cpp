#include "button.hpp"
#include "raylib.h"
#include "textlabel.hpp"
#include "yoga/YGNodeStyle.h"
#include <yoga/Yoga.h>

Button::Button(std::string text) : old_hovered(false) {
	this->text_label = new TextLabel(text);
	YGNodeStyleSetPaddingPercent(this->node, YGEdgeAll, 2);
	YGNodeStyleSetHeightPercent(this->node, 100);
	YGNodeInsertChild(this->node, this->text_label->node, 0);
}

Button::~Button() {
	delete text_label;
}

void Button::draw() {
	// Set position and size
	float width = YGNodeLayoutGetWidth(this->node);
	float height = YGNodeLayoutGetHeight(this->node);
	this->set_screen_pos();

	Color draw_color = this->color;
	if (this->hovered) {
		draw_color = ColorTint(draw_color, GRAY);
	}

	DrawRectangle(this->pos.x, this->pos.y, width, height, draw_color);

	text_label->draw();
}

void Button::late_step() {
	Container::late_step();

	// First time when the is_cursor_on changes
	if (this->hovered != this->old_hovered) {
		if (this->hovered) {
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
		} else {
			SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		}
	}

	this->old_hovered = this->hovered;
}
