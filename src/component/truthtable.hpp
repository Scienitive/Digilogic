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

struct TruthTableNode {
	TruthTableNode *left;
	TruthTableNode *right;
	std::vector<State> *outputs;

	TruthTableNode(size_t depth, std::vector<std::vector<State>> &outputs);
	~TruthTableNode();

	std::vector<std::vector<State>> get_outputs();

private:
	void get_outputs_helper(std::vector<std::vector<State>> &outputs);
};

#endif
