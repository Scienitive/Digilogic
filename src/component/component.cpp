#include "component.hpp"
#include "truthtable.hpp"
#include <cassert>
#include <cstddef>
#include <string>
#include <vector>

Component::Component(std::string name, size_t input_count, size_t output_count, LogicTable logictable)
	: name(name), input_count(input_count), output_count(output_count),
	  truth_table(new TruthTableNode(input_count, output_count, logictable)) {}

Component::Component(const Component &other) {
	*this = other;
}

Component &Component::operator=(const Component &other) {
	this->name = other.name;
	this->input_count = other.input_count;
	this->output_count = other.output_count;

	LogicTable logictable = other.truth_table->get_logictable();
	this->truth_table = new TruthTableNode(this->input_count, this->output_count, logictable);
	return *this;
}

Component::~Component() {
	if (this->truth_table != nullptr) {
		delete this->truth_table;
	}
}

size_t Component::get_input_count() {
	return this->input_count;
}

size_t Component::get_output_count() {
	return this->output_count;
}

std::string Component::get_name() {
	return this->name;
}

std::vector<State> *Component::simulate(std::vector<State> input) {
	// Check if input is valid
	assert(input.size() == this->input_count && "Error: Simulate input is not valid.");

	const TruthTableNode *node = this->truth_table;
	for (size_t i = 0; i < input.size(); i++) {
		if (input[i] == HIGH) {
			node = node->right;
		} else {
			node = node->left;
		}
	}
	return node->outputs;
}
