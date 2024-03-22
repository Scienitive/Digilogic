#include "app.hpp"
#include "component/componentgroup.hpp"
#include "object.hpp"
#include "raylib.h"
#include "ui/ui.hpp"

AppState::AppState() : exit(false) {}

AppState::~AppState() {}

void AppState::step() {
	SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

void AppState::late_step() {}

App::App() : comp_groups(initialize_component_groups()) {
	this->cam.target = {0.0f, 0.0f};
	this->cam.offset = {static_cast<float>(GetScreenWidth() / 2.0f), static_cast<float>(GetScreenHeight() / 2.0f)};
	this->cam.rotation = 0.0f;
	this->cam.zoom = 1.0f;

	// DELETE THESE
	Object a;
	Object b;
	b.world_pos = {50, 50};

	this->objects.push_back(a);
	this->objects.push_back(b);
}

App::~App() {}

App &App::get() {
	static App app;
	return app;
}

void App::resize_action() {
	this->cam.offset = {static_cast<float>(GetScreenWidth() / 2.0f), static_cast<float>(GetScreenHeight() / 2.0f)};
	UI::get().resize_action();
}

void App::step() {
	if (IsWindowResized()) {
		this->resize_action();
	}

	this->states.step();
	this->camera_controls();
	UI::get().step();
}

void App::draw() {
	BeginMode2D(this->cam);

	for (Object &obj : this->objects) {
		obj.draw();
	}

	EndMode2D();

	UI::get().draw();
}

void App::late_step() {
	this->states.late_step();
	UI::get().late_step();
}

const std::vector<ComponentGroup> App::get_comp_groups() {
	return this->comp_groups;
}
