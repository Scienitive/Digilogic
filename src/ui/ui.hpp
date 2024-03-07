#ifndef UI_HPP
#define UI_HPP

#include "button.hpp"
#include "container.hpp"
#include <functional>
#include <vector>

struct AllContainers {
	Container *main;

	Container *top;
	Container *mid;
	Container *bot;

	// Top
	Container *top_left;
	Container *top_middle;
	Container *top_right;

	// Top Left
	Button *github_button;

	// Top Right
	Button *settings_button;
	Button *exit_button;

	// Bottom
	std::vector<Button *> comp_group_buttons;
};

struct UI {
	AllContainers containers;

	UI();
	~UI();

private:
	void set_all_containers();
	void set_top_container(Color color, float height_perc, float height_min, float height_max);
	void set_mid_container();
	void set_bot_container(Color color, float height_perc, float height_min, float height_max);

	void apply_func_to_all_buttons(Container *cont, std::function<void(Button *)> func);

public:
	void step();
	void draw();
	void late_step();
	void calculate_layout();
};

#endif
