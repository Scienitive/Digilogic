#include "app.hpp"
#include "component/componentgroup.hpp"
#include "raylib.h"
#include "ui/ui.hpp"

AppState::AppState() : exit(false) {}

AppState::~AppState() {}

void AppState::step() {
	SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

App::App() : comp_groups(initialize_component_groups()) {}

App::~App() {}

App &App::get() {
	static App app;
	return app;
}

void App::step() {
	this->states.step();
	UI::get().step();
}

void App::draw() {
	UI::get().draw();
}

void App::late_step() {
	UI::get().late_step();
}

const std::vector<ComponentGroup> App::get_comp_groups() {
	return this->comp_groups;
}
