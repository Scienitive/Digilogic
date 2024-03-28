#include "ui.hpp"
#include "yoga/YGConfig.h"
#include "yoga/YGNode.h"
#include "yoga/YGNodeLayout.h"
#include <iostream>
#include <tuple>

// Negative values on min and max means disabled
static float mod_clamp(float value, float min, float max) {
	if (min >= 0 && value < min) {
		value = min;
	} else if (max >= 0 && value > max) {
		value = max;
	}
	return value;
}

static void set_border_percentages(Container *cont) {
	float width = YGNodeLayoutGetWidth(cont->node);
	float height = YGNodeLayoutGetHeight(cont->node);

	float border_top, border_top_min, border_top_max;
	float border_bottom, border_bottom_min, border_bottom_max;
	float border_left, border_left_min, border_left_max;
	float border_right, border_right_min, border_right_max;
	std::tie(border_top, border_top_min, border_top_max) = cont->get_border_top();
	std::tie(border_bottom, border_bottom_min, border_bottom_max) = cont->get_border_bottom();
	std::tie(border_left, border_left_min, border_left_max) = cont->get_border_left();
	std::tie(border_right, border_right_min, border_right_max) = cont->get_border_right();

	if (border_top >= 0) {
		float border_top_final = mod_clamp(height / 100 * border_top, border_top_min, border_top_max);
		YGNodeStyleSetBorder(cont->node, YGEdgeTop, border_top_final);
	}
	if (border_bottom >= 0) {
		float border_bottom_final = mod_clamp(height / 100 * border_bottom, border_bottom_min, border_bottom_max);
		YGNodeStyleSetBorder(cont->node, YGEdgeBottom, border_bottom_final);
	}
	if (border_left >= 0) {
		float border_left_final = mod_clamp(width / 100 * border_left, border_left_min, border_left_max);
		YGNodeStyleSetBorder(cont->node, YGEdgeLeft, border_left_final);
	}
	if (border_right >= 0) {
		float border_right_final = mod_clamp(width / 100 * border_right, border_right_min, border_right_max);
		YGNodeStyleSetBorder(cont->node, YGEdgeRight, border_right_final);
	}
}

static void set_gap_percentages(Container *cont) {
	YGNodeRef parent = YGNodeGetParent(cont->node);
	if (parent == nullptr) {
		return;
	}

	float p_width = YGNodeLayoutGetWidth(parent);
	float p_height = YGNodeLayoutGetHeight(parent);

	float gap_row, gap_row_min, gap_row_max;
	float gap_column, gap_column_min, gap_column_max;
	std::tie(gap_row, gap_row_min, gap_row_max) = cont->get_gap_row();
	std::tie(gap_column, gap_column_min, gap_column_max) = cont->get_gap_column();

	if (gap_row >= 0) {
		float gap_row_final = mod_clamp(p_height / 100 * gap_row, gap_row_min, gap_row_max);
		YGNodeStyleSetGap(cont->node, YGGutterRow, gap_row_final);
	}
	if (gap_column >= 0) {
		float gap_column_final = mod_clamp(p_width / 100 * gap_column, gap_column_min, gap_column_max);
		YGNodeStyleSetGap(cont->node, YGGutterColumn, gap_column_final);
	}
}

static void set_button_widths(Button *button) {
	if (button->text_label->text == "DELETE") {
		std::cout << YGNodeLayoutGetHeight(YGNodeGetParent(button->node)) << std::endl;
		std::cout << YGNodeLayoutGetHeight(button->node) << std::endl;
		std::cout << std::endl;
	}

	float text_width = button->text_label->set_font_size();

	// Recalculate borders for left and right
	float border_left_perc;
	float border_right_perc;

	float border_left, border_left_min, border_left_max;
	float border_right, border_right_min, border_right_max;
	std::tie(border_left, border_left_min, border_left_max) = button->get_border_left();
	std::tie(border_right, border_right_min, border_right_max) = button->get_border_right();

	if (border_left >= 0) {
		border_left_perc = mod_clamp(text_width / 100 * border_left, border_left_max, border_left_min);
		YGNodeStyleSetBorder(button->node, YGEdgeLeft, border_left_perc);
	} else {
		border_left_perc = YGNodeLayoutGetBorder(button->node, YGEdgeLeft);
	}
	if (border_right >= 0) {
		border_right_perc = mod_clamp(text_width / 100 * border_right, border_right_max, border_right_min);
		YGNodeStyleSetBorder(button->node, YGEdgeRight, border_right_perc);
	} else {
		border_right_perc = YGNodeLayoutGetBorder(button->node, YGEdgeRight);
	}

	button->width = text_width + border_left_perc + border_right_perc;
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

	// Set all modal width, height and positions
	this->apply_func_to_all<Modal>(this->containers.main, false, [](Modal *modal) { modal->calculate_layout(); });

	// Set all border percentage values
	this->apply_func_to_all<Container>(this->containers.main, true, set_border_percentages);
	// Set all gap percentage values
	this->apply_func_to_all<Container>(this->containers.main, true, set_gap_percentages);

	// Set all button widths
	this->apply_func_to_all<Button>(this->containers.main, false, set_button_widths);
	this->apply_func_to_all<Button>(this->containers.main, false, set_linked_button_widths);

	// TODO You can optimise this by only going through TextLabel's that don't belong to a button (because
	// button->textlabels are handled on button part of this function).
	this->apply_func_to_all<TextLabel>(this->containers.main, false,
									   [](TextLabel *text_label) { text_label->set_font_size(); });

	YGNodeCalculateLayout(this->containers.main->node, GetScreenWidth(), GetScreenHeight(), YGDirectionLTR);
}
