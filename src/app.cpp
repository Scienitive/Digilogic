#include "app.hpp"
#include "component/componentgroup.hpp"
#include "raylib.h"
#include "ui/ui.hpp"
#include <iostream>

AppState::AppState() : exit(false) {}

AppState::~AppState() {}

void AppState::step() {
	SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

App::App() : ui(UI::get()) {
	this->set_comp_groups();
}

App::~App() {}

App &App::get() {
	static App app;
	return app;
}

void App::step() {
	this->states.step();
	this->ui.step();
	ComponentGroup &a = this->comp_groups[0];
	std::cout << a.name << std::endl;
}

void App::draw() {
	this->ui.draw();
}

void App::late_step() {
	this->ui.late_step();
}

void App::set_comp_groups() {
	ComponentGroup default_cg = ComponentGroup("DEFAULT");
	this->comp_groups.push_back(default_cg);
}
