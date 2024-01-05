#ifndef SCENE_HPP
#define SCENE_HPP

#include "camera.hpp"
#include "component.hpp"
#include "ui.hpp"
#include <raylib.h>
#include <vector>

class App {
	Cam cam;
	UI ui;

	void initialize_built_in_components();

public:
	App();

	std::vector<ComponentGroup> get_comp_groups();

	void input_handler();
	void draw_scene();
	void draw_ui();
};

#endif
