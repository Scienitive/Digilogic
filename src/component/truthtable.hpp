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

using LogicTable = std::vector<std::vector<State>>;

struct TruthTableNode {
	TruthTableNode *left;
	TruthTableNode *right;
	std::vector<State> *outputs;

	TruthTableNode(size_t input_count, size_t output_count, LogicTable &logictable);
	~TruthTableNode();

	LogicTable get_logictable() const;

private:
	TruthTableNode(size_t depth, size_t input_count, size_t &count, LogicTable &logictable);

	void get_logictable_helper(LogicTable &logictable) const;
	bool is_logictable_valid(size_t input_count, size_t outputs, LogicTable &logictable) const;
};

#endif
