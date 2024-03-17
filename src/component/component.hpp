#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "truthtable.hpp"
#include <cstddef>
#include <string>
#include <vector>

class Component {
	std::string name;

	size_t input_count;
	size_t output_count;

	TruthTableNode *truth_table;

public:
	Component(std::string name, size_t input_count, size_t output_count, std::vector<std::vector<State>> outputs);
	~Component();
	Component(const Component &other) = delete;
	Component &operator=(const Component &other) = delete;

	size_t get_input_count();
	size_t get_output_count();
	std::string get_name();

	std::vector<State> *simulate(std::vector<State> input);
};

#endif
