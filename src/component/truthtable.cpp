#include "truthtable.hpp"
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>

std::ostream &operator<<(std::ostream &os, const State &state) {
	switch (state) {
	case LOW:
		os << "LOW";
		break;
	case HIGH:
		os << "HIGH";
		break;
	case HIGH_Z:
		os << "HIGH_Z";
		break;
	}
	return os;
}

TruthTableNode::TruthTableNode(size_t depth, size_t input_count, size_t &count, LogicTable &logictable)
	: left(nullptr), right(nullptr), outputs(nullptr) {
	if (depth < input_count - 1) {
		this->left = new TruthTableNode(depth + 1, input_count, count, logictable);
		this->right = new TruthTableNode(depth + 1, input_count, count, logictable);

	} else {
		this->outputs = new std::vector<State>(logictable[count]);
		count++;
	}
}

TruthTableNode::TruthTableNode(size_t input_count, size_t output_count, LogicTable &logictable)
	: left(nullptr), right(nullptr), outputs(nullptr) {
	assert(this->is_logictable_valid(input_count, output_count, logictable) && "Error: LogicTable is not valid.");

	size_t count = 0;
	this->left = new TruthTableNode(0, input_count, count, logictable);
	this->right = new TruthTableNode(0, input_count, count, logictable);
}

TruthTableNode::~TruthTableNode() {
	if (this->left != nullptr) {
		delete this->left;
	}
	if (this->right != nullptr) {
		delete this->right;
	}
	if (this->outputs != nullptr) {
		delete this->outputs;
	}
}

LogicTable TruthTableNode::get_logictable() const {
	LogicTable logictable;
	this->get_logictable_helper(logictable);
	return logictable;
}

void TruthTableNode::get_logictable_helper(LogicTable &logictable) const {
	if (this->left != nullptr && this->right != nullptr) {
		this->left->get_logictable_helper(logictable);
		this->right->get_logictable_helper(logictable);
	} else {
		logictable.push_back(*this->outputs);
	}
}

bool TruthTableNode::is_logictable_valid(size_t input_count, size_t output_count, LogicTable &logictable) const {
	if (logictable.size() != 1 << input_count) {
		return false;
	}
	for (std::vector<State> &output : logictable) {
		if (output.size() != output_count) {
			return false;
		}
	}
	return true;
}
