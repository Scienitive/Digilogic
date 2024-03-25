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

TruthTableNode::TruthTableNode() : left(nullptr), right(nullptr), outputs(nullptr) {}

TruthTableNode::TruthTableNode(size_t input_count, size_t output_count, LogicTable &logictable)
	: left(nullptr), right(nullptr), outputs(nullptr) {
	assert(this->is_logictable_valid(input_count, output_count, logictable) && "Error: LogicTable is not valid.");

	for (size_t i = 0; i < (1 << input_count); i++) {
		TruthTableNode *node = this;

		for (size_t j = 0; j < input_count; j++) {
			if (i & (1 << j)) {
				if (node->right == nullptr) {
					node->right = new TruthTableNode();
				}
				node = node->right;
			} else {
				if (node->left == nullptr) {
					node->left = new TruthTableNode();
				}
				node = node->left;
			}

			if (j == input_count - 1) {
				node->outputs = new std::vector<State>(logictable[i]);
			}
		}
	}
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

void TruthTableNode::get_logictable_helper(LogicTable &logictable) {
	if (this->left != nullptr && this->right != nullptr) {
		this->left->get_logictable_helper(logictable);
		this->right->get_logictable_helper(logictable);
	} else {
		logictable.push_back(*this->outputs);
	}
}

LogicTable TruthTableNode::get_logictable() {
	LogicTable logictable;
	this->get_logictable_helper(logictable);
	return logictable;
}

bool TruthTableNode::is_logictable_valid(size_t input_count, size_t output_count, LogicTable &logictable) {
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
