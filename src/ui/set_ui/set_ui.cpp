#include "set_ui.hpp"
#include "../ui.hpp"

static void set_all_modals(UI &ui) {
	set_exit_modal(ui);
}

void UI::set_all_containers() {
	// Top and bottom UI container settings
	Color top_bot_bg_color = {53, 51, 51, 255};
	float top_bot_height_percentage = 7;
	float top_bot_min_height_px = 42;
	float top_bot_max_height_px = 90;

	set_top_container(*this, top_bot_bg_color, top_bot_height_percentage, top_bot_min_height_px, top_bot_max_height_px);
	set_mid_container(*this);
	set_bot_container(*this, top_bot_bg_color, top_bot_height_percentage, top_bot_min_height_px, top_bot_max_height_px);

	set_all_modals(*this);
}
