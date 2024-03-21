#include "../../../app.hpp"
#include "../set_ui.hpp"

void set_exit_modal(UI &ui) {
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
	no_button->set_on_click([&ui]() {
		Modal *modal = ui.get_front_modal();
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
	ui.containers.main->add_child(exit_modal);
	ui.containers.exit_modal = exit_modal;
}
