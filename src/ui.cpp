#include "ui.hpp"
#include "raylib.h"
#include <cstddef>

UI::UI() {
	this->top_bar_color = YELLOW;
	this->bottom_bar_color = YELLOW;
	this->initialize_buttons();
}

int UI::get_top_bar_height() {
	const int MAX_HEIGHT = 64;
	const int MIN_HEIGHT = 32;

	int height = GetScreenHeight() / 12;
	if (height > MAX_HEIGHT) {
		height = MAX_HEIGHT;
	} else if (height < MIN_HEIGHT) {
		height = MIN_HEIGHT;
	}

	return height;
}

int UI::get_bottom_bar_height() {
	return this->get_top_bar_height();
}

void UI::initialize_buttons() {

	// Top Right Buttons
	Button exit_button("EXIT", this->get_top_bar_height() * BAR_BUTTON_HEIGHT_RATIO, PURPLE);
	Button settings_button("SETTINGS", this->get_top_bar_height() * BAR_BUTTON_HEIGHT_RATIO, PURPLE);
	this->top_right_buttons.push_back(exit_button);
	this->top_right_buttons.push_back(settings_button);

	// Top Left Buttons
	Button github_button("GITHUB", this->get_top_bar_height() * BAR_BUTTON_HEIGHT_RATIO, PURPLE);
	this->top_left_buttons.push_back(github_button);

	// Bottom Buttons handled on "add_comp_group" function.
}

void UI::draw_top_bar() {

	DrawRectangle(0, 0, GetScreenWidth(), this->get_top_bar_height(), this->top_bar_color);

	// Top Left Buttons
	for (std::size_t i = 0; i < this->top_left_buttons.size(); i++) {
		Button &button = this->top_left_buttons[i];

		int distance = 0;
		for (int j = i - 1; j >= 0; j--) {
			Button &prev_button = this->top_left_buttons[j];
			distance += prev_button.get_width() + BUTTON_GAP;
		}

		button.set_pos({
			static_cast<float>(SIDE_MARGIN + distance),
			static_cast<float>((this->get_top_bar_height() - button.get_height()) / 2.0f),
		});
		button.draw();
	}

	// Top Right Buttons
	for (std::size_t i = 0; i < this->top_right_buttons.size(); i++) {
		Button &button = this->top_right_buttons[i];

		int distance = 0;
		for (int j = i - 1; j >= 0; j--) {
			Button &prev_button = this->top_right_buttons[j];
			distance += prev_button.get_width() + BUTTON_GAP;
		}

		button.set_pos({
			static_cast<float>(GetScreenWidth() - button.get_width() - (SIDE_MARGIN + distance)),
			static_cast<float>((this->get_top_bar_height() - button.get_height()) / 2.0f),
		});
		button.draw();
	}
}

void UI::draw_bottom_bar() {
	DrawRectangle(0, GetScreenHeight() - this->get_bottom_bar_height(), GetScreenWidth(), this->get_top_bar_height(),
				  this->bottom_bar_color);

	int starting_pos = GetScreenWidth() / 2;
	int all_buttons_width = 0;
	for (Button &button : this->bottom_buttons) {
		all_buttons_width += button.get_width();
	}
	all_buttons_width += (this->bottom_buttons.size() - 1) * BUTTON_GAP;
	starting_pos -= all_buttons_width / 2;
	/* std::cout << this->bottom_buttons.size() << std::endl; */

	for (std::size_t i = 0; i < this->bottom_buttons.size(); i++) {
		Button &button = this->bottom_buttons[i];

		int distance = 0;
		for (int j = i - 1; j >= 0; j--) {
			Button &prev_button = this->bottom_buttons[j];
			distance += prev_button.get_width() + BUTTON_GAP;
		}

		button.set_pos({
			static_cast<float>(starting_pos + distance),
			static_cast<float>((GetScreenHeight() - button.get_height()) -
							   ((this->get_bottom_bar_height() - button.get_height()) / 2.0f)),
		});
		button.draw();
	}
}

void UI::draw() {
	this->draw_top_bar();
	this->draw_bottom_bar();
}

void UI::input_handler() {
	// Top Bar
	for (Button &button : this->top_left_buttons) {
		button.input_handler();
	}
	for (Button &button : this->top_right_buttons) {
		button.input_handler();
	}

	// Bottom Bar
	for (Button &button : this->bottom_buttons) {
		button.input_handler();
	}
}

void UI::add_comp_group(ComponentGroup group) {
	this->comp_groups.push_back(group);

	Button button(group.name, this->get_bottom_bar_height() * BAR_BUTTON_HEIGHT_RATIO, PURPLE);
	this->bottom_buttons.push_back(button);
}
