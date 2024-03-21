#ifndef SET_UI_HPP
#define SET_UI_HPP

#include "../ui.hpp"
#include <raylib.h>

// Containers
void set_top_container(UI &ui, Color color, float height_perc, float height_min, float height_max);
void set_mid_container(UI &ui);
void set_bot_container(UI &ui, Color color, float height_perc, float height_min, float height_max);

// Modals
void set_exit_modal(UI &ui);

#endif
