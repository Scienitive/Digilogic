#include "component.hpp"
#include "truthtable.hpp"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>

// class Component
Component::Component(std::string name, std::size_t input_count, std::size_t output_count,
					 std::vector<std::vector<State>> &outputs)
	: name(name), input_count(input_count), output_count(output_count),
	  truth_table(new TruthTableNode(input_count, outputs)) {}

Component::Component(const Component &comp)
	: name(comp.name), input_count(comp.input_count), output_count(comp.output_count), truth_table(NULL) {
	std::vector<std::vector<State>> outputs = comp.truth_table->get_outputs();
	this->truth_table = new TruthTableNode(this->input_count, outputs);
}

Component &Component::operator=(const Component &comp) {
	std::vector<std::vector<State>> outputs = comp.truth_table->get_outputs();
	this->name = comp.name;
	this->input_count = comp.input_count;
	this->output_count = comp.output_count;
	this->truth_table = new TruthTableNode(this->input_count, outputs);
	return *this;
}

Component::~Component() {
	if (this->truth_table != NULL) {
		delete this->truth_table;
	}
}

std::size_t Component::get_input_count() {
	return this->input_count;
}

std::size_t Component::get_output_count() {
	return this->output_count;
}

std::string Component::get_name() {
	return this->name;
}

std::vector<State> *Component::simulate(std::vector<State> &input) {
	TruthTableNode *node = this->truth_table;
	for (std::size_t i = 0; i < input.size(); i++) {
		if (input[i] == HIGH) {
			node = node->right;
		} else {
			node = node->left;
		}
	}
	return node->outputs;
}

// struct ComponentGroup
ComponentGroup::ComponentGroup(std::string name) : name(name) {}

// class ComponentObject
ComponentObject::ComponentObject(Component &comp) : comp(comp) {
	for (std::size_t i = 0; i < this->comp.get_input_count(); i++) {
		this->input.push_back(LOW);
	}
}

void ComponentObject::simulate() {
	this->output = this->comp.simulate(this->input);

	// Delete This
	for (State &element : *this->output) {
		std::cout << element << " ";
	}
	std::cout << std::endl;
}

void ComponentObject::change_input(std::vector<State> input) {
	if (input.size() != this->input.size()) {
		std::cerr << "Input Change Error\n";
		exit(1);
	}
	this->input = input;
}
