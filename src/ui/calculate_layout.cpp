#include "ui.hpp"

// Negative values on min and max means disabled
static float clamp(float value, float max, float min) {
	if (max >= 0 && value > max) {
		value = max;
	} else if (min >= 0 && value < min) {
		value = min;
	}
	return value;
}

static void set_border_percentages(Container *cont) {
	float width = YGNodeLayoutGetWidth(cont->node);
	float height = YGNodeLayoutGetHeight(cont->node);

	if (cont->border_top >= 0) {
		float border_top = clamp(height / 100 * cont->border_top, cont->border_top_max, cont->border_top_min);
		YGNodeStyleSetBorder(cont->node, YGEdgeTop, border_top);
	}
	if (cont->border_bottom >= 0) {
		float border_bottom =
			clamp(height / 100 * cont->border_bottom, cont->border_bottom_max, cont->border_bottom_min);
		YGNodeStyleSetBorder(cont->node, YGEdgeBottom, border_bottom);
	}
	if (cont->border_left >= 0) {
		float border_left = clamp(width / 100 * cont->border_left, cont->border_left_max, cont->border_left_min);
		YGNodeStyleSetBorder(cont->node, YGEdgeLeft, border_left);
	}
	if (cont->border_right >= 0) {
		float border_right = clamp(width / 100 * cont->border_right, cont->border_right_max, cont->border_right_min);
		YGNodeStyleSetBorder(cont->node, YGEdgeRight, border_right);
	}
}

static void set_button_widths(Button *button) {
	float text_width = button->text_label->set_font_size();

	// Recalculate borders for left and right
	float border_left;
	float border_right;
	if (button->border_left >= 0) {
		border_left = clamp(text_width / 100 * button->border_left, button->border_left_max, button->border_left_min);
		YGNodeStyleSetBorder(button->node, YGEdgeLeft, border_left);
	} else {
		border_left = YGNodeLayoutGetBorder(button->node, YGEdgeLeft);
	}
	if (button->border_right >= 0) {
		border_right =
			clamp(text_width / 100 * button->border_right, button->border_right_max, button->border_right_min);
		YGNodeStyleSetBorder(button->node, YGEdgeRight, border_right);
	} else {
		border_right = YGNodeLayoutGetBorder(button->node, YGEdgeRight);
	}

	button->width = text_width + border_left + border_right;
	YGNodeStyleSetWidth(button->node, button->width);
}

static void set_linked_button_widths(Button *button) {
	for (Button *linked : button->width_linked_buttons) {
		if (linked->width > button->width) {
			button->width = linked->width;
		}
		if (linked->width_multiplier > button->width_multiplier) {
			button->width_multiplier = linked->width_multiplier;
		}
	}
	YGNodeStyleSetWidth(button->node, button->width * button->width_multiplier);
}

void UI::calculate_layout() {
	YGNodeCalculateLayout(this->containers.main->node, GetScreenWidth(), GetScreenHeight(), YGDirectionLTR);

	// Set all border percentage values
	this->apply_func_to_all<Container>(this->containers.main, true, set_border_percentages);

	// Set all button widths
	this->apply_func_to_all<Button>(this->containers.main, false, set_button_widths);
	this->apply_func_to_all<Button>(this->containers.main, false, set_linked_button_widths);

	// Set all modal width, height and positions
	this->apply_func_to_all<Modal>(this->containers.main, false, [](Modal *modal) { modal->calculate_layout(); });

	// TODO You can optimise this by only going through TextLabel's that don't belong to a button (because
	// button->textlabels are handled on button part of this function).
	this->apply_func_to_all<TextLabel>(this->containers.main, false,
									   [](TextLabel *text_label) { text_label->set_font_size(); });

	YGNodeCalculateLayout(this->containers.main->node, GetScreenWidth(), GetScreenHeight(), YGDirectionLTR);
}
