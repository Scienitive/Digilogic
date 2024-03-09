#include "ui.hpp"
#include "button.hpp"
#include "container.hpp"
#include "yoga/YGNodeLayout.h"
#include <raylib.h>
#include <yoga/YGNodeStyle.h>
#include <yoga/Yoga.h>

UI::UI() {
	// Set main_container and it's properties
	this->containers.main = new Container();
	this->containers.main->color = {217, 217, 217, 255};
	YGNodeStyleSetFlexDirection(this->containers.main->node, YGFlexDirectionColumn);
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

UI &UI::get() {
	static UI ui;
	return ui;
}

void UI::step() {
	// Recalculate Layout if
	if (IsWindowResized()) {
		this->calculate_layout();
	}

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

void UI::apply_func_to_all_buttons(Container *cont, std::function<void(Button *)> func) {
	Button *possible_button = dynamic_cast<Button *>(cont);
	if (possible_button != nullptr) {
		func(possible_button);
	} else {
		for (Container *c : cont->get_children()) {
			apply_func_to_all_buttons(c, func);
		}
	}
}

void UI::apply_func_to_all_modals(Container *cont, std::function<void(Modal *)> func) {
	Modal *possible_modal = dynamic_cast<Modal *>(cont);
	if (possible_modal != nullptr) {
		func(possible_modal);
	} else {
		for (Container *c : cont->get_children()) {
			apply_func_to_all_modals(c, func);
		}
	}
}

void UI::calculate_layout() {
	YGNodeCalculateLayout(this->containers.main->node, GetScreenWidth(), GetScreenHeight(), YGDirectionLTR);

	// Set all button widths
	this->apply_func_to_all_buttons(this->containers.main, [](Button *button) {
		float padding_top = YGNodeLayoutGetPadding(button->node, YGEdgeTop);
		float padding_bot = YGNodeLayoutGetPadding(button->node, YGEdgeBottom);
		float padding_left = YGNodeLayoutGetPadding(button->node, YGEdgeLeft);
		float padding_right = YGNodeLayoutGetPadding(button->node, YGEdgeRight);

		float height = YGNodeLayoutGetHeight(button->node) - (padding_top + padding_bot);
		float width = button->text_label->set_size_from_height(height) + (padding_left + padding_right);
		YGNodeStyleSetWidth(button->node, width);
	});

	// Set all modal width, height and positions
	this->apply_func_to_all_modals(this->containers.main, [](Modal *modal) { modal->calculate_layout(); });

	YGNodeCalculateLayout(this->containers.main->node, GetScreenWidth(), GetScreenHeight(), YGDirectionLTR);
}

void UI::set_all_containers() {
	// Top and bottom UI container settings
	Color top_bot_bg_color = {53, 51, 51, 255};
	float top_bot_height_percentage = 7;
	float top_bot_min_height_px = 42;
	float top_bot_max_height_px = 90;

	this->set_top_container(top_bot_bg_color, top_bot_height_percentage, top_bot_min_height_px, top_bot_max_height_px);
	this->set_mid_container();
	this->set_bot_container(top_bot_bg_color, top_bot_height_percentage, top_bot_min_height_px, top_bot_max_height_px);

	this->set_all_modals();
}

void UI::set_all_modals() {
	Modal *exit_modal = new Modal();
	exit_modal->color = RED;
	exit_modal->set_size(16.0 / 9.0, 20, 300);
	this->containers.main->add_child(exit_modal);
	this->containers.exit_modal = exit_modal;
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
	YGNodeStyleSetPadding(top_left->node, YGEdgeTop, 8);
	YGNodeStyleSetPadding(top_left->node, YGEdgeBottom, 8);
	YGNodeStyleSetPaddingPercent(top_left->node, YGEdgeLeft, 0.8);
	YGNodeStyleSetPaddingPercent(top_left->node, YGEdgeRight, 0.8);
	YGNodeStyleSetGap(top_left->node, YGGutterColumn, 12);
	YGNodeStyleSetWidthPercent(top_middle->node, 34);
	YGNodeStyleSetHeightPercent(top_middle->node, 100);
	YGNodeStyleSetFlexDirection(top_middle->node, YGFlexDirectionRow);
	YGNodeStyleSetPadding(top_middle->node, YGEdgeTop, 8);
	YGNodeStyleSetPadding(top_middle->node, YGEdgeBottom, 8);
	YGNodeStyleSetPaddingPercent(top_middle->node, YGEdgeLeft, 0.8);
	YGNodeStyleSetPaddingPercent(top_middle->node, YGEdgeRight, 0.8);
	YGNodeStyleSetWidthPercent(top_right->node, 33);
	YGNodeStyleSetHeightPercent(top_right->node, 100);
	YGNodeStyleSetFlexDirection(top_right->node, YGFlexDirectionRow);
	YGNodeStyleSetPadding(top_right->node, YGEdgeTop, 8);
	YGNodeStyleSetPadding(top_right->node, YGEdgeBottom, 8);
	YGNodeStyleSetPaddingPercent(top_right->node, YGEdgeLeft, 0.8);
	YGNodeStyleSetPaddingPercent(top_right->node, YGEdgeRight, 0.8);
	YGNodeStyleSetGap(top_right->node, YGGutterColumn, 12);
	YGNodeStyleSetJustifyContent(top_right->node, YGJustifyFlexEnd);

	// Top Left
	Button *github_button = new Button("GITHUB");
	github_button->color = {40, 211, 108, 255};
	github_button->set_on_click([]() { OpenURL("https://github.com/Scienitive/Digilogic"); });
	this->containers.top_left->add_child(github_button);
	this->containers.github_button = github_button;

	// Top Right
	Button *settings_button = new Button("SETTINGS");
	settings_button->color = {40, 201, 211, 255};
	this->containers.top_right->add_child(settings_button);
	this->containers.settings_button = settings_button;

	Button *exit_button = new Button("EXIT");
	exit_button->color = {211, 40, 40, 255};
	exit_button->set_on_click([this]() { this->containers.exit_modal->activate(); });
	this->containers.top_right->add_child(exit_button);
	this->containers.exit_button = exit_button;
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
