#include "ui.hpp"
#include "button.hpp"
#include "container.hpp"
#include "yoga/YGNodeLayout.h"
#include <iostream>
#include <raylib.h>
#include <yoga/YGNodeStyle.h>
#include <yoga/Yoga.h>

UI::UI() {
	// Set main_container and it's properties
	this->containers.main = new Container();
	this->containers.main->color = {217, 217, 217, 255};
	YGNodeStyleSetFlexDirection(this->containers.main->node, YGFlexDirectionColumn);
	/* YGNodeStyleSetHeightAuto(this->containers.main.node); */
	/* YGNodeStyleSetWidthAuto(this->containers.main.node); */
	YGNodeStyleSetWidthPercent(this->containers.main->node, 100);
	YGNodeStyleSetHeightPercent(this->containers.main->node, 100);
	YGNodeStyleSetJustifyContent(this->containers.main->node, YGJustifySpaceBetween);

	// Run initial UI functions
	this->set_all_containers();
	this->calculate_layout();
}

UI::~UI() {
	YGNodeFreeRecursive(this->containers.main->node);
}

void UI::step() {
	// Recalculate Layout if
	if (IsWindowResized()) {
		this->calculate_layout();
	}
}

void UI::draw() {
	this->containers.main->draw();
}

void UI::calculate_layout() {
	YGNodeCalculateLayout(this->containers.main->node, GetScreenWidth(), GetScreenHeight(), YGDirectionLTR);

	// Set all button widths
	float padding_top = YGNodeLayoutGetPadding(this->containers.github_button->node, YGEdgeTop);
	float padding_bot = YGNodeLayoutGetPadding(this->containers.github_button->node, YGEdgeBottom);
	float padding_left = YGNodeLayoutGetPadding(this->containers.github_button->node, YGEdgeLeft);
	float padding_right = YGNodeLayoutGetPadding(this->containers.github_button->node, YGEdgeRight);

	float height = YGNodeLayoutGetHeight(this->containers.github_button->node) - (padding_top + padding_bot);
	float width = this->containers.github_button->text_label->set_size_from_height(height);
	YGNodeStyleSetWidth(this->containers.github_button->node, width + padding_left + padding_right);

	YGNodeCalculateLayout(this->containers.main->node, GetScreenWidth(), GetScreenHeight(), YGDirectionLTR);
}

void UI::set_all_containers() {
	// Top and bottom UI container settings
	Color top_bot_bg_color = {53, 51, 51, 255};
	float top_bot_height_percentage = 8;
	float top_bot_min_height_px = 42;
	float top_bot_max_height_px = 90;

	this->set_top_container(top_bot_bg_color, top_bot_height_percentage, top_bot_min_height_px, top_bot_max_height_px);
	this->set_mid_container();
	this->set_bot_container(top_bot_bg_color, top_bot_height_percentage, top_bot_min_height_px, top_bot_max_height_px);
}

void UI::set_top_container(Color color, float height_perc, float height_min, float height_max) {
	// Top
	Container *top = new Container();
	top->color = color;
	YGNodeStyleSetHeightPercent(top->node, height_perc);
	YGNodeStyleSetMinHeight(top->node, height_min);
	YGNodeStyleSetMaxHeight(top->node, height_max);
	YGNodeStyleSetFlexDirection(top->node, YGFlexDirectionRow);
	this->containers.main->add_child(top);
	this->containers.top = top;

	// Top Children
	Container *top_left = new Container();
	this->containers.top->add_child(top_left);
	this->containers.top_left = top_left;
	Container *top_middle = new Container();
	this->containers.top->add_child(top_middle);
	this->containers.top_middle = top_middle;
	Container *top_right = new Container();
	this->containers.top->add_child(top_right);
	this->containers.top_right = top_right;

	// Width, Height, Padding and FlexDirection Settings
	YGNodeStyleSetWidthPercent(top_left->node, 33);
	YGNodeStyleSetHeightPercent(top_left->node, 100);
	YGNodeStyleSetFlexDirection(top_left->node, YGFlexDirectionRow);
	YGNodeStyleSetPaddingPercent(top_left->node, YGEdgeAll, 0.8);
	YGNodeStyleSetWidthPercent(top_middle->node, 34);
	YGNodeStyleSetHeightPercent(top_middle->node, 100);
	YGNodeStyleSetFlexDirection(top_middle->node, YGFlexDirectionRow);
	YGNodeStyleSetPaddingPercent(top_middle->node, YGEdgeAll, 0.8);
	YGNodeStyleSetWidthPercent(top_right->node, 33);
	YGNodeStyleSetHeightPercent(top_right->node, 100);
	YGNodeStyleSetFlexDirection(top_right->node, YGFlexDirectionRow);
	YGNodeStyleSetPaddingPercent(top_right->node, YGEdgeAll, 0.8);

	// Top Left
	top_left->color = RED;
	Button *github_button = new Button("GITHUB");
	github_button->color = GREEN;
	this->containers.top_left->add_child(github_button);
	this->containers.github_button = github_button;
}

void UI::set_bot_container(Color color, float height_perc, float height_min, float height_max) {
	Container *bot = new Container();
	bot->color = color;
	YGNodeStyleSetHeightPercent(bot->node, height_perc);
	YGNodeStyleSetMinHeight(bot->node, height_min);
	YGNodeStyleSetMaxHeight(bot->node, height_max);
	this->containers.main->add_child(bot);
	this->containers.bot = bot;
}

void UI::set_mid_container() {
	Container *mid = new Container();
	YGNodeStyleSetFlexGrow(mid->node, 1);
	this->containers.main->add_child(mid);
	this->containers.mid = mid;
}
