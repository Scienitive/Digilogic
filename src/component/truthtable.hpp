#ifndef TRUTHTABLE_HPP
#define TRUTHTABLE_HPP

#include <cstddef>
#include <ostream>
#include <vector>

enum State {
	LOW,
	HIGH,
	HIGH_Z,
};
std::ostream &operator<<(std::ostream &os, const State &state);
typedef std::vector<std::vector<State>> LogicTable;

struct TruthTableNode {
	TruthTableNode *left;
	TruthTableNode *right;
	std::vector<State> *outputs;

	TruthTableNode(size_t depth, LogicTable &outputs);
	~TruthTableNode();

	LogicTable get_outputs();

private:
	void get_outputs_helper(LogicTable &outputs);
};

#endif
