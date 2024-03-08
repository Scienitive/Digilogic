#include "app.hpp"
#include "ui/ui.hpp"

App::App() : ui(UI::get()) {}

App::~App() {}

App &App::get() {
	static App app;
	return app;
}

void App::step() {
	this->ui.step();
}

void App::draw() {
	this->ui.draw();
}

void App::late_step() {
	this->ui.late_step();
}
