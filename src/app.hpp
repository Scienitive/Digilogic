#ifndef APP_HPP
#define APP_HPP

#include "component/componentgroup.hpp"
#include <vector>

struct AppState {
	bool exit;

	AppState();
	~AppState();

	void step();
};

struct App {
	AppState states;

private:
	std::vector<ComponentGroup> comp_groups;

public:
	static App &get();
	~App();
	App(const App &other) = delete;
	App &operator=(const App &other) = delete;

	void step();
	void draw();
	void late_step();

	const std::vector<ComponentGroup> get_comp_groups();

private:
	App();

	void set_comp_groups();
};

#endif
