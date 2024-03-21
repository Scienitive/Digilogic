#ifndef COMPONENTGROUP_HPP
#define COMPONENTGROUP_HPP

#include "component.hpp"
#include <string>
#include <vector>

struct ComponentGroup {
	std::string name;
	std::vector<Component> components;

	ComponentGroup(std::string name);
	~ComponentGroup();
};

std::vector<ComponentGroup> initialize_component_groups();

#endif
