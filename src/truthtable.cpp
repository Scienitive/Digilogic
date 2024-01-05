#include "truthtable.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>

// enum State
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

// struct TruthTableNode
TruthTableNode::TruthTableNode(std::size_t depth, std::vector<std::vector<State>> &outputs)
	: left(NULL), right(NULL), outputs(NULL) {
	if (depth > 0) {
		this->left = new TruthTableNode(depth - 1, outputs);
		this->right = new TruthTableNode(depth - 1, outputs);
	} else {
		if (outputs.size() <= 0) {
			std::cerr << "TruthTableNode Leaf Nodes Filling Error\n";
			exit(1);
		}
		this->outputs = new std::vector<State>(outputs[0]);
		outputs.erase(outputs.begin());
	}
}

TruthTableNode::~TruthTableNode() {
	if (this->left != NULL) {
		delete this->left;
	}
	if (this->right != NULL) {
		delete this->right;
	}
	if (this->outputs != NULL) {
		delete this->outputs;
	}
}

void TruthTableNode::get_outputs_helper(std::vector<std::vector<State>> &outputs) {
	if (this->left != NULL && this->right != NULL) {
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
