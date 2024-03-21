#include "ui.hpp"
#include "../app.hpp"
#include <cstddef>
#include <fstream>
#include <functional>
#include <raylib.h>
#include <yoga/YGNode.h>
#include <yoga/YGNodeLayout.h>
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

void debug_containers_recursive(std::ofstream &file, Container *cont) {
	Button *button = dynamic_cast<Button *>(cont);
	TextLabel *text_label = dynamic_cast<TextLabel *>(cont);
	Modal *modal = dynamic_cast<Modal *>(cont);

	file << "type: ";
	if (button != nullptr) {
		file << "Button\n";
		file << "info: " << button->text_label->text << "\n";
	} else if (text_label != nullptr) {
		file << "TextLabel\n";
		file << "info: " << text_label->text << "\n";
	} else if (modal != nullptr) {
		file << "Modal\n";
	} else {
		file << "Container\n";
	}

	file << "given width: " << YGNodeStyleGetWidth(cont->node).value;
	if (YGNodeStyleGetWidth(cont->node).unit == 2) {
		file << "%\n";
	} else {
		file << "px\n";
	}
	file << "calculated width: " << YGNodeLayoutGetWidth(cont->node) << "\n";
	file << "given height: " << YGNodeStyleGetHeight(cont->node).value;
	if (YGNodeStyleGetHeight(cont->node).unit == 2) {
		file << "%\n";
	} else {
		file << "px\n";
	}
	file << "calculated height: " << YGNodeLayoutGetHeight(cont->node) << "\n";
	file << "given padding all: " << YGNodeStyleGetPadding(cont->node, YGEdgeAll).value;
	if (YGNodeStyleGetPadding(cont->node, YGEdgeAll).unit == 2) {
		file << "%\n";
	} else {
		file << "px\n";
	}
	file << "given padding top: " << YGNodeStyleGetPadding(cont->node, YGEdgeTop).value;
	if (YGNodeStyleGetPadding(cont->node, YGEdgeTop).unit == 2) {
		file << "%\n";
	} else {
		file << "px\n";
	}
	file << "calculated padding top: " << YGNodeLayoutGetPadding(cont->node, YGEdgeTop) << "\n";
	file << "calculated padding bottom: " << YGNodeLayoutGetPadding(cont->node, YGEdgeBottom) << "\n";
	file << "calculated padding left: " << YGNodeLayoutGetPadding(cont->node, YGEdgeLeft) << "\n";
	file << "calculated padding right: " << YGNodeLayoutGetPadding(cont->node, YGEdgeRight) << "\n";
	file << "\n";

	for (Container *child : cont->get_children()) {
		debug_containers_recursive(file, child);
	}
}

void UI::debug_containers() {
	std::ofstream file("logs", std::ofstream::trunc);
	if (file.is_open()) {
		debug_containers_recursive(file, this->containers.main);
		file.close();
	}
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
	exit_modal->color = {53, 51, 51, 255};
	exit_modal->set_size(16.0 / 9.0, 25, 225);
	YGNodeStyleSetFlexDirection(exit_modal->node, YGFlexDirectionColumn);

	Container *exit_modal_top = new Container();
	Container *exit_modal_bot = new Container();
	Button *no_button = new Button("NO");
	Button *yes_button = new Button("YES");
	TextLabel *exit_modal_text = new TextLabel("Are you sure?");

	// Exit Modal Bot
	YGNodeStyleSetWidthPercent(exit_modal_bot->node, 100);
	YGNodeStyleSetHeightPercent(exit_modal_bot->node, 50);
	YGNodeStyleSetJustifyContent(exit_modal_bot->node, YGJustifySpaceEvenly);
	YGNodeStyleSetFlexDirection(exit_modal_bot->node, YGFlexDirectionRow);
	YGNodeStyleSetPaddingPercent(exit_modal_bot->node, YGEdgeAll, 7.5);
	exit_modal_bot->add_child(no_button);
	exit_modal_bot->add_child(yes_button);

	no_button->width_link_button(yes_button);
	no_button->width_multiplier = 2;
	no_button->color = RED;
	no_button->set_on_click([this]() {
		Modal *modal = this->get_front_modal();
		modal->deactivate();
	});

	yes_button->color = GREEN;
	yes_button->set_on_click([]() {
		App &app = App::get();
		app.states.exit = true;
	});

	exit_modal_text->text_color = WHITE;

	// Exit Modal Top
	YGNodeStyleSetHeightPercent(exit_modal_text->node, 50);

	YGNodeStyleSetJustifyContent(exit_modal_top->node, YGJustifyCenter);
	YGNodeStyleSetAlignItems(exit_modal_top->node, YGAlignCenter);
	YGNodeStyleSetWidthPercent(exit_modal_top->node, 100);
	YGNodeStyleSetHeightPercent(exit_modal_top->node, 50);
	exit_modal_top->add_child(exit_modal_text);

	// Exit Modal
	exit_modal->add_child(exit_modal_top);
	exit_modal->add_child(exit_modal_bot);
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
	YGNodeStyleSetPadding(top->node, YGEdgeTop, 8);
	YGNodeStyleSetPadding(top->node, YGEdgeBottom, 8);
	YGNodeStyleSetPaddingPercent(top->node, YGEdgeLeft, 0.8);
	YGNodeStyleSetPaddingPercent(top->node, YGEdgeRight, 0.8);
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
	YGNodeStyleSetGap(top_left->node, YGGutterColumn, 12);
	YGNodeStyleSetWidthPercent(top_middle->node, 34);
	YGNodeStyleSetHeightPercent(top_middle->node, 100);
	YGNodeStyleSetFlexDirection(top_middle->node, YGFlexDirectionRow);
	YGNodeStyleSetWidthPercent(top_right->node, 33);
	YGNodeStyleSetHeightPercent(top_right->node, 100);
	YGNodeStyleSetFlexDirection(top_right->node, YGFlexDirectionRow);
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
	YGNodeStyleSetFlexDirection(bot->node, YGFlexDirectionRow);
	YGNodeStyleSetJustifyContent(bot->node, YGJustifyCenter);
	YGNodeStyleSetAlignItems(bot->node, YGAlignCenter);
	YGNodeStyleSetGap(bot->node, YGGutterColumn, 20);
	YGNodeStyleSetPadding(bot->node, YGEdgeTop, 8);
	YGNodeStyleSetPadding(bot->node, YGEdgeBottom, 8);
	YGNodeStyleSetPaddingPercent(bot->node, YGEdgeLeft, 0.8);
	YGNodeStyleSetPaddingPercent(bot->node, YGEdgeRight, 0.8);
	this->containers.main->add_child(bot);
	this->containers.bot = bot;

	const std::vector<ComponentGroup> &comp_groups = App::get().get_comp_groups();
	for (const ComponentGroup &comp_group : comp_groups) {
		Button *button = new Button(comp_group.name);
		button->color = {107, 126, 114, 255};

		this->containers.bot->add_child(button);
		this->containers.comp_group_buttons.push_back(button);
	}
}

void UI::set_mid_container() {
	Container *mid = new Container();
	YGNodeStyleSetFlexGrow(mid->node, 1);
	this->containers.main->add_child(mid);
	this->containers.mid = mid;
}

Modal *UI::get_front_modal() {
	if (this->active_modals.empty()) {
		return nullptr;
	} else {
		return this->active_modals.back();
	}
}
