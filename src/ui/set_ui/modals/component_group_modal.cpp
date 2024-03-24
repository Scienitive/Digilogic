#include "../set_ui.hpp"
#include <iostream>
#include <yoga/YGNodeStyle.h>

void set_component_group_modal(UI &ui, ComponentGroup &cg) {
	Modal *modal = new Modal();
	modal->color = {53, 51, 51, 255};
	modal->set_size(14.0 / 9.0, 75, 2000);
	YGNodeStyleSetFlexDirection(modal->node, YGFlexDirectionRow);
	YGNodeStyleSetGap(modal->node, YGGutterAll, 10);
	YGNodeStyleSetFlexWrap(modal->node, YGWrapWrap);

	for (Component &comp : cg.components) {
		Container *comp_container = new Container();
		comp_container->color = RED;
		YGNodeStyleSetWidth(comp_container->node, 80);
		YGNodeStyleSetHeight(comp_container->node, 80);

		modal->add_child(comp_container);
	}

	// Dont forget to delete the old one
	ui.containers.main->add_child(modal);
	ui.containers.comp_group_modal = modal;

	// This can be made better if I only calculate this component somehow.
	ui.calculate_layout();
}
