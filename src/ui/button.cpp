#include "button.hpp"
#include "raylib.h"
#include "textlabel.hpp"
#include "ui.hpp"
#include "yoga/YGNodeStyle.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <yoga/Yoga.h>

Button::Button(std::string text) : width(0), on_click([]() {}), old_hovered(false) {
	this->text_label = new TextLabel(text);
	YGNodeStyleSetPaddingPercent(this->node, YGEdgeAll, 2);
	YGNodeStyleSetHeightPercent(this->node, 100);
	YGNodeInsertChild(this->node, this->text_label->node, 0);

	// Center the textlabel and potentially other elements inside the button
	YGNodeStyleSetAlignItems(this->node, YGAlignCenter);
	YGNodeStyleSetJustifyContent(this->node, YGJustifyCenter);
}

Button::~Button() {
	delete text_label;
}

void Button::step() {
	Container::step();

	// The first time the cursor enters or leaves
	/* if (this->hovered != this->old_hovered) { */
	/* 	if (this->hovered) { */
	/* 	} */
	/* } */

	// Continously checking if the cursor is in the container
	if (this->hovered) {
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
		// Left click
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			this->on_click();
		}
	}

	this->old_hovered = this->hovered;
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
}

void Button::set_on_click(std::function<void()> func) {
	this->on_click = func;
}

// This could be better if you use set or unordered_set
void Button::width_link_button(Button *other) {
	if (std::find(this->width_linked_buttons.begin(), this->width_linked_buttons.end(), other) ==
		this->width_linked_buttons.end()) {
		this->width_linked_buttons.push_back(other);
		other->width_linked_buttons.push_back(this);
	}
}
