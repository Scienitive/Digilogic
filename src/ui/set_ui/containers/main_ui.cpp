#include "../../../app.hpp"
#include "../../ui.hpp"
#include "../set_ui.hpp"
#include <raylib.h>
#include <yoga/Yoga.h>

void set_top_container(UI &ui, Color color, float height_perc, float height_min, float height_max) {
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
	ui.containers.main->add_child(top);
	ui.containers.top = top;

	// Top Children
	Container *top_left = new Container();
	ui.containers.top->add_child(top_left);
	ui.containers.top_left = top_left;
	Container *top_middle = new Container();
	ui.containers.top->add_child(top_middle);
	ui.containers.top_middle = top_middle;
	Container *top_right = new Container();
	ui.containers.top->add_child(top_right);
	ui.containers.top_right = top_right;

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
	ui.containers.top_left->add_child(github_button);
	ui.containers.github_button = github_button;

	// Top Right
	Button *settings_button = new Button("SETTINGS");
	settings_button->color = {40, 201, 211, 255};
	ui.containers.top_right->add_child(settings_button);
	ui.containers.settings_button = settings_button;

	Button *exit_button = new Button("EXIT");
	exit_button->color = {211, 40, 40, 255};
	exit_button->set_on_click([&ui]() { ui.containers.exit_modal->activate(); });
	ui.containers.top_right->add_child(exit_button);
	ui.containers.exit_button = exit_button;
}

void set_bot_container(UI &ui, Color color, float height_perc, float height_min, float height_max) {
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
	ui.containers.main->add_child(bot);
	ui.containers.bot = bot;

	const std::vector<ComponentGroup> &comp_groups = App::get().get_comp_groups();
	for (const ComponentGroup &comp_group : comp_groups) {
		Button *button = new Button(comp_group.name);
		button->color = {107, 126, 114, 255};

		ui.containers.bot->add_child(button);
		ui.containers.comp_group_buttons.push_back(button);
	}
}

void set_mid_container(UI &ui) {
	Container *mid = new Container();
	YGNodeStyleSetFlexGrow(mid->node, 1);
	ui.containers.main->add_child(mid);
	ui.containers.mid = mid;
}
