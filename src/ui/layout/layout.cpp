#include "layout.hpp"

Layout::Layout() {}
Layout::~Layout() {}

void Layout::set_type(LType type) {
	this->type = type;
}

void Layout::set_primary(LPrimary value) {
	this->primary = value;
}

void Layout::set_secondary(LSecondary value) {
	this->secondary = value;
}

void Layout::set_grow(bool value) {
	this->grow = value;
}

void Layout::set_wrap(bool value) {
	this->wrap = value;
}

std::vector<LClamp> Layout::gap_gutter_helper(LGutter gutter) {
	std::vector<LClamp> vec;
	switch (gutter) {
	case LGutterPrimary:
		vec.push_back(this->gap.primary);
		break;
	case LGutterSecondary:
		vec.push_back(this->gap.secondary);
		break;
	case LGutterAll:
		vec.push_back(this->gap.primary);
		vec.push_back(this->gap.secondary);
		break;
	}
	return vec;
}

void Layout::set_gap(LGutter gutter, LValueType type, float value) {
	std::vector<LClamp> vec = this->gap_gutter_helper(gutter);
	for (LClamp &cla : vec) {
		cla.value.type = type;
		cla.value.value = value;
	}
}

void Layout::set_gap_min(LGutter gutter, LValueType type, float value) {
	std::vector<LClamp> vec = this->gap_gutter_helper(gutter);
	for (LClamp &cla : vec) {
		cla.min.type = type;
		cla.min.value = value;
	}
}

void Layout::set_gap_max(LGutter gutter, LValueType type, float value) {
	std::vector<LClamp> vec = this->gap_gutter_helper(gutter);
	for (LClamp &cla : vec) {
		cla.max.type = type;
		cla.max.value = value;
	}
}

void Layout::set_left(LValueType type, float value) {
	this->left.type = type;
	this->left.value = value;
}

void Layout::set_top(LValueType type, float value) {
	this->top.type = type;
	this->top.value = value;
}

void Layout::set_width(LValueType type, float value) {
	this->width.value.type = type;
	this->width.value.value = value;
}

void Layout::set_width_min(LValueType type, float value) {
	this->width.min.type = type;
	this->width.min.value = value;
}

void Layout::set_width_max(LValueType type, float value) {
	this->width.max.type = type;
	this->width.max.value = value;
}

void Layout::set_height(LValueType type, float value) {
	this->height.value.type = type;
	this->height.value.value = value;
}

void Layout::set_height_min(LValueType type, float value) {
	this->height.min.type = type;
	this->height.min.value = value;
}

void Layout::set_height_max(LValueType type, float value) {
	this->height.max.type = type;
	this->height.max.value = value;
}

std::vector<LClamp> Layout::margin_edge_helper(LEdge edge) {
	std::vector<LClamp> vec;
	switch (edge) {
	case LEdgeLeft:
		vec.push_back(this->margin.left);
		break;
	case LEdgeRight:
		vec.push_back(this->margin.right);
		break;
	case LEdgeTop:
		vec.push_back(this->margin.top);
		break;
	case LEdgeBottom:
		vec.push_back(this->margin.bottom);
		break;
	case LEdgeHorizontal:
		vec.push_back(this->margin.left);
		vec.push_back(this->margin.right);
		break;
	case LEdgeVertical:
		vec.push_back(this->margin.top);
		vec.push_back(this->margin.bottom);
	case LEdgeAll:
		vec.push_back(this->margin.left);
		vec.push_back(this->margin.right);
		vec.push_back(this->margin.top);
		vec.push_back(this->margin.bottom);
	}
	return vec;
}

void Layout::set_margin(LEdge edge, LValueType type, float value) {
	std::vector<LClamp> vec = this->margin_edge_helper(edge);
	for (LClamp &cla : vec) {
		cla.value.type = type;
		cla.value.value = value;
	}
}

void Layout::set_margin_min(LEdge edge, LValueType type, float value) {
	std::vector<LClamp> vec = this->margin_edge_helper(edge);
	for (LClamp &cla : vec) {
		cla.min.type = type;
		cla.min.value = value;
	}
}

void Layout::set_margin_max(LEdge edge, LValueType type, float value) {
	std::vector<LClamp> vec = this->margin_edge_helper(edge);
	for (LClamp &cla : vec) {
		cla.max.type = type;
		cla.max.value = value;
	}
}

std::vector<LClamp> Layout::padding_edge_helper(LEdge edge) {
	std::vector<LClamp> vec;
	switch (edge) {
	case LEdgeLeft:
		vec.push_back(this->padding.left);
		break;
	case LEdgeRight:
		vec.push_back(this->padding.right);
		break;
	case LEdgeTop:
		vec.push_back(this->padding.top);
		break;
	case LEdgeBottom:
		vec.push_back(this->padding.bottom);
		break;
	case LEdgeHorizontal:
		vec.push_back(this->padding.left);
		vec.push_back(this->padding.right);
		break;
	case LEdgeVertical:
		vec.push_back(this->padding.top);
		vec.push_back(this->padding.bottom);
	case LEdgeAll:
		vec.push_back(this->padding.left);
		vec.push_back(this->padding.right);
		vec.push_back(this->padding.top);
		vec.push_back(this->padding.bottom);
	}
	return vec;
}

void Layout::set_padding(LEdge edge, LValueType type, float value) {
	std::vector<LClamp> vec = this->padding_edge_helper(edge);
	for (LClamp &cla : vec) {
		cla.value.type = type;
		cla.value.value = value;
	}
}

void Layout::set_padding_min(LEdge edge, LValueType type, float value) {
	std::vector<LClamp> vec = this->padding_edge_helper(edge);
	for (LClamp &cla : vec) {
		cla.min.type = type;
		cla.min.value = value;
	}
}

void Layout::set_padding_max(LEdge edge, LValueType type, float value) {
	std::vector<LClamp> vec = this->padding_edge_helper(edge);
	for (LClamp &cla : vec) {
		cla.max.type = type;
		cla.max.value = value;
	}
}

Layout *Layout::get_parent() {
	return this->parent;
}

std::vector<Layout> &Layout::get_children() {
	return this->children;
}

void Layout::add_child(Layout &&child) {
	this->children.push_back(child);
}

void Layout::calculate() {
	// Calculate width and height
	if (this->parent != nullptr) {

	} else {
	}
}
