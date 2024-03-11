#ifndef UI_HPP
#define UI_HPP

#include "button.hpp"
#include "container.hpp"
#include "modal.hpp"
#include <functional>
#include <vector>

struct AllContainers {
	Container *main;

	Container *top;
	Container *mid;
	Container *bot;

	// Modals
	Modal *exit_modal;

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
	std::vector<Modal *> active_modals;

	static UI &get();
	~UI();
	UI(const UI &other) = delete;
	UI &operator=(const UI &other) = delete;

private:
	UI();

	void set_all_containers();
	void set_all_modals();
	void set_top_container(Color color, float height_perc, float height_min, float height_max);
	void set_mid_container();
	void set_bot_container(Color color, float height_perc, float height_min, float height_max);

	template <typename T> void apply_func_to_all(Container *cont, std::function<void(T *)> func);

	void default_close_modal_func();

public:
	void calculate_layout();

	void step();
	void draw();
	void late_step();
};

#endif
