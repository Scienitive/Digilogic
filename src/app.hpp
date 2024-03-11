#ifndef APP_HPP
#define APP_HPP

#include "ui/ui.hpp"

struct State {
	bool exit;

	State();
	~State();

	void step();
};

struct App {
	UI &ui;
	State states;

	static App &get();
	~App();
	App(const App &other) = delete;
	App &operator=(const App &other) = delete;

	void step();
	void draw();
	void late_step();

private:
	App();
};

#endif
