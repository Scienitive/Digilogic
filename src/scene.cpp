#include "scene.hpp"
#include <raylib.h>
#include <vector>

App::App() {
	this->initialize_built_in_components();
}

void App::initialize_built_in_components() {
	ComponentGroup built_in = ComponentGroup("BUILT-INS");

	// NOT GATE
	std::vector<std::vector<State>> not_outputs = {
		{HIGH},
		{LOW},
	};
	Component not_gate = Component("NOT", 1, 1, not_outputs);

	// AND GATE
	std::vector<std::vector<State>> and_outputs = {
		{LOW},
		{LOW},
		{LOW},
		{HIGH},
	};
	Component and_gate = Component("AND", 2, 1, and_outputs);

	// OR GATE
	std::vector<std::vector<State>> or_outputs = {
		{LOW},
		{HIGH},
		{HIGH},
		{HIGH},
	};
	Component or_gate = Component("OR", 2, 1, or_outputs);

	// XOR GATE
	std::vector<std::vector<State>> xor_outputs = {
		{LOW},
		{HIGH},
		{HIGH},
		{LOW},
	};
	Component xor_gate = Component("XOR", 2, 1, xor_outputs);

	// NAND GATE
	std::vector<std::vector<State>> nand_outputs = {
		{HIGH},
		{HIGH},
		{HIGH},
		{LOW},
	};
	Component nand_gate = Component("NAND", 2, 1, nand_outputs);

	// NOR GATE
	std::vector<std::vector<State>> nor_outputs = {
		{HIGH},
		{LOW},
		{LOW},
		{LOW},
	};
	Component nor_gate = Component("NOR", 2, 1, nor_outputs);

	// XNOR GATE
	std::vector<std::vector<State>> xnor_outputs = {
		{HIGH},
		{LOW},
		{LOW},
		{HIGH},
	};
	Component xnor_gate = Component("XNOR", 2, 1, xnor_outputs);

	// BUILT-INS GROUP
	built_in.components.push_back(not_gate);
	built_in.components.push_back(and_gate);
	built_in.components.push_back(or_gate);
	built_in.components.push_back(xor_gate);
	built_in.components.push_back(nand_gate);
	built_in.components.push_back(nor_gate);
	built_in.components.push_back(xnor_gate);
	this->ui.add_comp_group(built_in);
}

void App::draw_scene() {
	this->cam.draw_component_world({0, 0}, {100, 100}, GREEN);
	this->cam.draw_component_world({-140, 140}, {100, 100}, BLUE);
}

void App::draw_ui() {
	this->ui.draw();
}

void App::input_handler() {
	this->cam.input_handler();
	this->ui.input_handler();
}
