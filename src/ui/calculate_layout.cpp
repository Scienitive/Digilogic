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

	float border_top = clamp(height / 100 * cont->border_top, cont->border_top_max, cont->border_top_min);
	float border_bottom = clamp(height / 100 * cont->border_bottom, cont->border_bottom_max, cont->border_bottom_min);
	float border_left = clamp(width / 100 * cont->border_left, cont->border_left_max, cont->border_left_min);
	float border_right = clamp(width / 100 * cont->border_right, cont->border_right_max, cont->border_right_min);

	if (cont->border_top >= 0) {
		YGNodeStyleSetBorder(cont->node, YGEdgeTop, border_top);
	}
	if (cont->border_bottom >= 0) {
		YGNodeStyleSetBorder(cont->node, YGEdgeBottom, border_bottom);
	}
	if (cont->border_left >= 0) {
		YGNodeStyleSetBorder(cont->node, YGEdgeLeft, border_left);
	}
	if (cont->border_right >= 0) {
		YGNodeStyleSetBorder(cont->node, YGEdgeRight, border_right);
	}
}

void UI::calculate_layout() {
	YGNodeCalculateLayout(this->containers.main->node, GetScreenWidth(), GetScreenHeight(), YGDirectionLTR);

	// Set all border percentage values
	this->apply_func_to_all<Container>(this->containers.main, true, set_border_percentages);

	/* YGNodeCalculateLayout(this->containers.main->node, GetScreenWidth(), GetScreenHeight(), YGDirectionLTR); */

	// Set all button widths
	this->apply_func_to_all<Button>(this->containers.main, false, [](Button *button) {
		float text_width = button->text_label->set_font_size();

		// Recalculate borders for left and right because width was 0
		float border_left;
		float border_right;
		if (button->border_left < 0) {
			border_left = YGNodeLayoutGetBorder(button->node, YGEdgeLeft);
		} else {
			border_left = text_width / 100 * button->border_left;
			if (button->border_left_max >= 0 && border_left > button->border_left_max) {
				border_left = button->border_left_max;
			} else if (button->border_left_min >= 0 && border_left < button->border_left_min) {
				border_left = button->border_left_min;
			}
			YGNodeStyleSetBorder(button->node, YGEdgeLeft, border_left);
		}
		if (button->border_right < 0) {
			border_right = YGNodeLayoutGetBorder(button->node, YGEdgeRight);
		} else {
			border_right = text_width / 100 * button->border_right;
			if (button->border_right_max >= 0 && border_right > button->border_right_max) {
				border_right = button->border_right_max;
			} else if (button->border_right_min >= 0 && border_right < button->border_right_min) {
				border_right = button->border_right_min;
			}
			YGNodeStyleSetBorder(button->node, YGEdgeRight, border_right);
		}

		button->width = text_width + border_left + border_right;
		YGNodeStyleSetWidth(button->node, button->width);
	});
	this->apply_func_to_all<Button>(this->containers.main, false, [](Button *button) {
		for (Button *linked : button->width_linked_buttons) {
			if (linked->width > button->width) {
				button->width = linked->width;
			}
			if (linked->width_multiplier > button->width_multiplier) {
				button->width_multiplier = linked->width_multiplier;
			}
		}
		YGNodeStyleSetWidth(button->node, button->width * button->width_multiplier);
	});

	// Set all modal width, height and positions
	this->apply_func_to_all<Modal>(this->containers.main, false, [](Modal *modal) { modal->calculate_layout(); });

	// TODO You can optimise this by only going through TextLabel's that don't belong to a button (because
	// button->textlabels are handled on button part of this function).
	this->apply_func_to_all<TextLabel>(this->containers.main, false,
									   [](TextLabel *text_label) { text_label->set_font_size(); });

	YGNodeCalculateLayout(this->containers.main->node, GetScreenWidth(), GetScreenHeight(), YGDirectionLTR);
	this->debug_containers();
}
