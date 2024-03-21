#include "componentgroup.hpp"
#include "component.hpp"

ComponentGroup::ComponentGroup(std::string name) : name(name) {}

ComponentGroup::~ComponentGroup() {}

static void set_not_gate(ComponentGroup &group) {
	LogicTable not_logic = {
		{HIGH},
		{LOW},
	};
	group.components.push_back(Component("NOT", 1, 1, not_logic));
}

static void set_and_gate(ComponentGroup &group) {
	LogicTable and_logic = {
		{LOW},
		{LOW},
		{LOW},
		{HIGH},
	};
	group.components.push_back(Component("AND", 2, 1, and_logic));
}

static void set_or_gate(ComponentGroup &group) {
	LogicTable or_logic = {
		{LOW},
		{HIGH},
		{HIGH},
		{HIGH},
	};
	group.components.push_back(Component("OR", 2, 1, or_logic));
}

static void set_xor_gate(ComponentGroup &group) {
	LogicTable xor_logic = {
		{LOW},
		{HIGH},
		{HIGH},
		{LOW},
	};
	group.components.push_back(Component("XOR", 2, 1, xor_logic));
}

static void set_nand_gate(ComponentGroup &group) {
	LogicTable nand_logic = {
		{HIGH},
		{HIGH},
		{HIGH},
		{LOW},
	};
	group.components.push_back(Component("NAND", 2, 1, nand_logic));
}

static void set_nor_gate(ComponentGroup &group) {
	LogicTable nor_logic = {
		{HIGH},
		{LOW},
		{LOW},
		{LOW},
	};
	group.components.push_back(Component("NOR", 2, 1, nor_logic));
}

static void set_xnor_gate(ComponentGroup &group) {
	LogicTable xnor_logic = {
		{HIGH},
		{LOW},
		{LOW},
		{HIGH},
	};
	group.components.push_back(Component("XNOR", 2, 1, xnor_logic));
}

std::vector<ComponentGroup> initialize_component_groups() {
	std::vector<ComponentGroup> comp_groups;

	ComponentGroup built_in_cg = ComponentGroup("BUILT-INS");
	ComponentGroup default_cg = ComponentGroup("DEFAULT");

	set_not_gate(built_in_cg);
	set_and_gate(built_in_cg);
	set_or_gate(built_in_cg);
	set_xor_gate(built_in_cg);
	set_nand_gate(built_in_cg);
	set_nor_gate(built_in_cg);
	set_xnor_gate(built_in_cg);

	comp_groups.push_back(built_in_cg);
	comp_groups.push_back(default_cg);
	return comp_groups;
}
