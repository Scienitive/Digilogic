#ifndef APP_HPP
#define APP_HPP

#include "component/componentgroup.hpp"
#include "object.hpp"
#include <raylib.h>
#include <vector>

struct AppState {
	// General
	bool exit;

	AppState();
	~AppState();

	void step();
	void late_step();
};

struct App {
	AppState states;
	Camera2D cam;

private:
	std::vector<Object> objects;
	std::vector<ComponentGroup> comp_groups;

public:
	static App &get();
	~App();
	App(const App &other) = delete;
	App &operator=(const App &other) = delete;

	void resize_action();
	void step();
	void draw();
	void late_step();

	std::vector<ComponentGroup> &get_comp_groups();

private:
	App();

	void set_comp_groups();
	void camera_controls();
};

#endif
