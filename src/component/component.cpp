#include "component.hpp"
#include "truthtable.hpp"
#include <cstddef>
#include <string>
#include <vector>

Component::Component(std::string name, size_t input_count, size_t output_count, LogicTable outputs)
	: name(name), input_count(input_count), output_count(output_count),
	  truth_table(new TruthTableNode(input_count, outputs)) {}

Component::Component(const Component &other) {
	*this = other;
}

Component &Component::operator=(const Component &other) {
	this->name = other.name;
	this->input_count = other.input_count;
	this->output_count = other.output_count;

	LogicTable outputs = other.truth_table->get_outputs();
	this->truth_table = new TruthTableNode(this->input_count, outputs);
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
	TruthTableNode *node = this->truth_table;
	for (size_t i = 0; i < input.size(); i++) {
		if (input[i] == HIGH) {
			node = node->right;
		} else {
			node = node->left;
		}
	}
	return node->outputs;
}
