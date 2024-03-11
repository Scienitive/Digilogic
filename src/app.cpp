#include "app.hpp"
#include "raylib.h"
#include "ui/ui.hpp"

State::State() {}

State::~State() {}

void State::step() {
	SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

App::App() : ui(UI::get()) {}

App::~App() {}

App &App::get() {
	static App app;
	return app;
}

void App::step() {
	this->states.step();
	this->ui.step();
}

void App::draw() {
	this->ui.draw();
}

void App::late_step() {
	this->ui.late_step();
}
