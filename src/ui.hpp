#ifndef UI_HPP
#define UI_HPP

#include "button.hpp"
#include "component.hpp"
#include <vector>

class UI {
	// Constants
	const int SIDE_MARGIN = 16;
	const int BUTTON_GAP = 16;
	const float BAR_BUTTON_HEIGHT_RATIO = 0.8f;

	std::vector<ComponentGroup> comp_groups;

	// Top Bar
	Color top_bar_color;
	std::vector<Button> top_left_buttons;
	std::vector<Button> top_right_buttons;

	// Bottom Bar
	Color bottom_bar_color;
	std::vector<Button> bottom_buttons;

	void initialize_buttons();
	int get_top_bar_height();
	int get_bottom_bar_height();

	void draw_top_bar();
	void draw_bottom_bar();

public:
	UI();

	void draw();
	void input_handler();
	void add_comp_group(ComponentGroup group);
};

#endif
