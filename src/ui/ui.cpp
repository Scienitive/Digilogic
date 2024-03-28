#include "ui.hpp"
#include "../app.hpp"
#include <cstddef>
#include <iostream>
#include <raylib.h>
#include <yoga/YGNode.h>
#include <yoga/YGNodeLayout.h>
#include <yoga/YGNodeStyle.h>
#include <yoga/Yoga.h>

UI::UI() {
	// Set main_container and it's properties
	this->containers.main = new Container();
	YGNodeStyleSetFlexDirection(this->containers.main->node, YGFlexDirectionColumn);
	YGNodeStyleSetWidthPercent(this->containers.main->node, 100);
	YGNodeStyleSetHeightPercent(this->containers.main->node, 100);
	YGNodeStyleSetJustifyContent(this->containers.main->node, YGJustifySpaceBetween);

	// Run initial UI functions
	this->set_all_containers();
	this->calculate_layout();
	// BUG When you do calculate_layout() just once somethings gets calculated wrongly (if you do it second time it's
	// ok) So this is a temporary fix
	this->calculate_layout();
}

UI::~UI() {
	YGNodeFreeRecursive(this->containers.main->node);
}

UI &UI::get() {
	static UI ui;
	return ui;
}

void UI::resize_action() {
	// BUG Well this is fucked up but otherwise it doesn't work properly for somethings
	// I think YogaLayout is not a great UI Layout Engine
	// I need to rewrite the all calculate_layout system if it becomes slow and effects the program heavily
	// but for now I'm going to make this dirty like this
	for (size_t i = 0; i < 2; i++) {
		this->calculate_layout();
	}
}

void UI::early_step() {
	this->containers.main->early_step();
}

void UI::step() {
	this->containers.main->step();
}

void UI::draw() {
	this->containers.main->draw();

	size_t active_modal_count = this->active_modals.size();
	for (size_t i = 0; i < active_modal_count; i++) {
		if (i == active_modal_count - 1) {
			DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), {0, 0, 0, 180});
		}
		Modal *modal = this->active_modals[i];
		modal->draw();
	}
}

void UI::late_step() {
	this->containers.main->late_step();
}

Modal *UI::get_front_modal() {
	if (this->active_modals.empty()) {
		return nullptr;
	} else {
		return this->active_modals.back();
	}
}
