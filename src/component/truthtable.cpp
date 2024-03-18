#include "truthtable.hpp"
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

TruthTableNode::TruthTableNode(size_t depth, std::vector<std::vector<State>> &outputs)
	: left(nullptr), right(nullptr), outputs(nullptr) {
	if (depth > 0) {
		this->left = new TruthTableNode(depth - 1, outputs);
		this->right = new TruthTableNode(depth - 1, outputs);
	} else {
		if (outputs.size() <= 0) {
			std::cerr << "TruthTableNode Leaf Nodes Filling Error" << std::endl;
			exit(1);
		}
		this->outputs = new std::vector<State>(outputs[0]);
		/* outputs.erase(outputs.begin()); // BU KISMA BI BAK BU COK SACMA BI DIZAYN (SIMDILIK DEVRE DISI AMA PROBLEM
		 * OLURSA BAK BURAYA) */
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

void TruthTableNode::get_outputs_helper(std::vector<std::vector<State>> &outputs) {
	if (this->left != nullptr && this->right != nullptr) {
		this->left->get_outputs_helper(outputs);
		this->right->get_outputs_helper(outputs);
	} else {
		outputs.push_back(*this->outputs);
	}
}

std::vector<std::vector<State>> TruthTableNode::get_outputs() {
	std::vector<std::vector<State>> outputs;
	this->get_outputs_helper(outputs);
	return outputs;
}
