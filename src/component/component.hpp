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

	const TruthTableNode *truth_table;

public:
	Component(std::string name, size_t input_count, size_t output_count, LogicTable logictable);
	Component(const Component &other);
	Component &operator=(const Component &other);
	~Component();

	size_t get_input_count();
	size_t get_output_count();
	std::string get_name();

	std::vector<State> *simulate(std::vector<State> input);
};

#endif
