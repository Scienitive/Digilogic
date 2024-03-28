#include "../set_ui.hpp"
#include <yoga/YGNodeStyle.h>

static Container *set_comp_container(std::string comp_group_name) {
	Container *cont = new Container();
	YGNodeStyleSetFlexDirection(cont->node, YGFlexDirectionColumn);
	YGNodeStyleSetWidthPercent(cont->node, 30);
	YGNodeStyleSetHeightPercent(cont->node, 30);

	Container *top = new Container();
	top->color = BLUE;
	YGNodeStyleSetWidthPercent(top->node, 100);
	YGNodeStyleSetFlexGrow(top->node, 1);

	Container *bot = new Container();
	bot->color = GREEN;
	YGNodeStyleSetFlexDirection(bot->node, YGFlexDirectionRow);
	YGNodeStyleSetJustifyContent(bot->node, YGJustifyCenter);
	YGNodeStyleSetWidthPercent(bot->node, 100);
	YGNodeStyleSetHeightPercent(bot->node, 27.5);
	bot->set_border_percent(YGEdgeVertical, 20);
	/* YGNodeStyleSetGap(bot->node, YGGutterColumn, 10); */
	bot->set_gap_percent(YGGutterColumn, 10);
	// WARN I need to add a MAX HEIGHT here

	Button *select_button = new Button("SELECT");
	select_button->color = RED;
	bot->add_child(select_button);

	Button *edit_button = new Button("EDIT");
	edit_button->color = RED;
	bot->add_child(edit_button);

	Button *delete_button = new Button("DELETE");
	delete_button->color = RED;
	bot->add_child(delete_button);

	cont->add_child(top);
	cont->add_child(bot);
	return cont;
}

void set_component_group_modal(UI &ui, ComponentGroup &cg) {
	Modal *modal = new Modal();
	modal->color = {53, 51, 51, 255};
	modal->set_size(14.0 / 9.0, 75, 2000);
	YGNodeStyleSetFlexDirection(modal->node, YGFlexDirectionRow);
	YGNodeStyleSetJustifyContent(modal->node, YGJustifyCenter);
	YGNodeStyleSetGap(modal->node, YGGutterAll, 10);
	YGNodeStyleSetFlexWrap(modal->node, YGWrapWrap);
	modal->set_border_percent(YGEdgeAll, 5);

	for (Component &comp : cg.components) {

		Container *comp_container = set_comp_container(cg.name);

		modal->add_child(comp_container);
	}

	// Dont forget to delete the old one
	ui.containers.main->add_child(modal);
	ui.containers.comp_group_modal = modal;

	// This can be made better if I only calculate this component somehow.
	ui.calculate_layout();
}
