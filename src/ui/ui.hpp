#ifndef UI_HPP
#define UI_HPP

#include "button/button.hpp"
#include "container/container.hpp"
#include "modal/modal.hpp"
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

	// if continue_nested == false: it wont search for another <T> under a <T> after finding one
	template <typename T>
	void apply_func_to_all(Container *cont, bool continue_nested, std::function<void(T *)> func) {
		T *possible_type = dynamic_cast<T *>(cont);
		if (possible_type != nullptr) {
			func(possible_type);
		}
		if (continue_nested || possible_type == nullptr) {
			for (Container *c : cont->get_children()) {
				apply_func_to_all<T>(c, continue_nested, func);
			}
		}
	}

public:
	void calculate_layout();

	void step();
	void draw();
	void late_step();

	Modal *get_front_modal();
};

#endif
