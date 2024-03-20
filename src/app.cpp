#include "app.hpp"
#include "component/component.hpp"
#include "component/componentgroup.hpp"
#include "component/truthtable.hpp"
#include "raylib.h"
#include "ui/ui.hpp"
#include <iostream>

AppState::AppState() : exit(false) {}

AppState::~AppState() {}

void AppState::step() {
	SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

App::App() {
	this->set_comp_groups();
}

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

void App::set_comp_groups() {
	ComponentGroup built_in_cg = ComponentGroup("BUILT-INS");

	LogicTable not_logic = {
		{HIGH},
		{LOW},
	};
	Component not_gate = Component("NOT", 1, 1, not_logic);

	LogicTable and_logic = {
		{LOW},
		{LOW},
		{LOW},
		{HIGH},
	};
	Component and_gate = Component("AND", 2, 1, and_logic);

	LogicTable or_logic = {
		{LOW},
		{HIGH},
		{HIGH},
		{HIGH},
	};
	Component or_gate = Component("OR", 2, 1, or_logic);

	LogicTable xor_logic = {
		{LOW},
		{HIGH},
		{HIGH},
		{LOW},
	};
	Component xor_gate = Component("XOR", 2, 1, xor_logic);

	LogicTable nand_logic = {
		{HIGH},
		{HIGH},
		{HIGH},
		{LOW},
	};
	Component nand_gate = Component("NAND", 2, 1, nand_logic);

	LogicTable nor_logic = {
		{HIGH},
		{LOW},
		{LOW},
		{LOW},
	};
	Component nor_gate = Component("NOR", 2, 1, nor_logic);

	LogicTable xnor_logic = {
		{HIGH},
		{LOW},
		{LOW},
		{HIGH},
	};
	Component xnor_gate = Component("XNOR", 2, 1, xnor_logic);

	built_in_cg.components.push_back(not_gate);
	built_in_cg.components.push_back(and_gate);
	built_in_cg.components.push_back(or_gate);
	built_in_cg.components.push_back(xor_gate);
	built_in_cg.components.push_back(nand_gate);
	built_in_cg.components.push_back(nor_gate);
	built_in_cg.components.push_back(xnor_gate);

	ComponentGroup default_cg = ComponentGroup("DEFAULT");

	this->comp_groups.push_back(built_in_cg);
	this->comp_groups.push_back(default_cg);
}
