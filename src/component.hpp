#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "truthtable.hpp"
#include <cstddef>
#include <string>
#include <vector>

class Component {
	std::string name;

	std::size_t input_count;
	std::size_t output_count;

	TruthTableNode *truth_table;

public:
	Component(std::string name, std::size_t input_count, std::size_t output_count,
			  std::vector<std::vector<State>> &outputs);
	Component(const Component &comp);
	Component &operator=(const Component &comp);
	~Component();

	std::size_t get_input_count();
	std::size_t get_output_count();
	std::string get_name();

	std::vector<State> *simulate(std::vector<State> &input);
};

struct ComponentGroup {
	std::string name;
	std::vector<Component> components;

	ComponentGroup(std::string name);
};

class ComponentObject {
	Component &comp;
	std::vector<State> input;
	std::vector<State> *output;

public:
	ComponentObject(Component &comp);

	void simulate();
	void change_input(std::vector<State> input);
};

#endif
