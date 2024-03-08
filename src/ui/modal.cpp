#include "modal.hpp"
#include "ui.hpp"
#include "yoga/YGNodeStyle.h"
#include <yoga/Yoga.h>

Modal::Modal() : active(false) {
	YGNodeStyleSetPositionType(this->node, YGPositionTypeAbsolute);
}

Modal::~Modal() {}

void Modal::set_size(float width_percentage, float height_percentage) {
	YGNodeStyleSetWidthPercent(this->node, width_percentage);
	YGNodeStyleSetHeightPercent(this->node, height_percentage);

	// Position setting
	YGNodeStyleSetPositionPercent(this->node, YGEdgeLeft, 50 - (width_percentage / 2));
	YGNodeStyleSetPositionPercent(this->node, YGEdgeTop, 50 - (height_percentage / 2));
}

void Modal::step() {
	Container::step();
}

void Modal::draw() {
	if (active) {
		Container::draw();
	}
}

void Modal::late_step() {
	Container::late_step();
}

void Modal::activate() {
	this->active = true;
	UI::get().modal_mode = true;
}

void Modal::deactivate() {
	this->active = false;
	UI::get().modal_mode = false;
}

bool Modal::is_active() {
	return this->active;
}
