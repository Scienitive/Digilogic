#include "modal.hpp"
#include "raylib.h"
#include "ui.hpp"
#include "yoga/YGNode.h"
#include "yoga/YGNodeStyle.h"
#include <iostream>
#include <yoga/Yoga.h>

Modal::Modal() : active(false) {
	YGNodeStyleSetPositionType(this->node, YGPositionTypeAbsolute);
}

Modal::~Modal() {}

void Modal::set_size(float aspect_ratio, float height_percentage, float height_max_px) {
	this->aspect_ratio = aspect_ratio;
	this->height_percentage = height_percentage;
	this->height_max_px = height_max_px;
}

void Modal::calculate_layout() {
	YGNodeStyleSetAspectRatio(this->node, this->aspect_ratio);
	YGNodeStyleSetHeightPercent(this->node, this->height_percentage);
	YGNodeStyleSetMaxHeight(this->node, this->height_max_px);
	YGNodeStyleSetMaxWidth(this->node, this->aspect_ratio * this->height_max_px);
	YGNodeCalculateLayout(this->node, GetScreenWidth(), GetScreenHeight(), YGDirectionLTR);

	float height = YGNodeLayoutGetHeight(this->node);
	float width = this->aspect_ratio * height;

	// Position setting
	YGNodeStyleSetPosition(this->node, YGEdgeLeft, (GetScreenWidth() / 2.0) - (width / 2.0));
	YGNodeStyleSetPosition(this->node, YGEdgeTop, (GetScreenHeight() / 2.0) - (height / 2.0));
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
	UI::get().active_modals.push_back(this);
}

void Modal::deactivate() {
	this->active = false;
	UI::get().active_modals.pop_back();
}

bool Modal::is_active() {
	return this->active;
}
