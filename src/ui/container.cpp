#include "container.hpp"
#include "modal.hpp"
#include "raylib.h"
#include "ui.hpp"
#include "yoga/YGNode.h"
#include "yoga/YGNodeLayout.h"

Container::Container()
	: color(BLANK), border_top(-1), border_bottom(-1), border_left(-1), border_right(-1), border_top_max(-1),
	  border_top_min(-1), border_bottom_max(-1), border_bottom_min(-1), border_left_max(-1), border_left_min(-1),
	  border_right_max(-1), border_right_min(-1) {
	this->node = YGNodeNew();
}

Container::~Container() {
	for (Container *cont : this->children) {
		delete cont;
	}
}

void Container::step() {
	UI &ui = UI::get();
	size_t active_modal_count = ui.active_modals.size();
	if (this == ui.containers.main || active_modal_count <= 0 || this == ui.active_modals[active_modal_count - 1] ||
		(this->am_i_child_of_this(ui.active_modals[active_modal_count - 1]))) {
		this->set_hovered();

		for (Container *cont : this->children) {
			cont->step();
		}
	}
}

void Container::draw() {
	// Set position and size
	float width = YGNodeLayoutGetWidth(this->node);
	float height = YGNodeLayoutGetHeight(this->node);
	this->set_screen_pos();

	DrawRectangle(this->pos.x, this->pos.y, width, height, this->color);

	for (Container *cont : this->children) {
		Modal *modal = dynamic_cast<Modal *>(cont);
		if (modal == nullptr) {
			cont->draw();
		}
	}
}

void Container::late_step() {
	for (Container *cont : this->children) {
		cont->late_step();
	}
}

void Container::set_hovered() {
	Vector2 cursor_pos = GetMousePosition();
	Vector2 size = {YGNodeLayoutGetWidth(this->node), YGNodeLayoutGetHeight(this->node)};

	if ((cursor_pos.x >= this->pos.x && cursor_pos.x <= this->pos.x + size.x) && cursor_pos.y >= this->pos.y &&
		cursor_pos.y <= this->pos.y + size.y) {
		this->hovered = true;
	} else {
		this->hovered = false;
	}
}

bool Container::am_i_child_of_this(Container *cont) {
	YGNodeRef parent = YGNodeGetParent(this->node);
	while (parent != nullptr) {
		if (cont->node == parent) {
			return true;
		}
		parent = YGNodeGetParent(parent);
	}
	return false;
}

void Container::set_screen_pos() {
	float x = YGNodeLayoutGetLeft(this->node);
	float y = YGNodeLayoutGetTop(this->node);
	YGNode *parent = YGNodeGetParent(this->node);
	while (parent != nullptr) {
		x += YGNodeLayoutGetLeft(parent) + YGNodeLayoutGetMargin(parent, YGEdgeLeft);
		y += YGNodeLayoutGetTop(parent) + YGNodeLayoutGetMargin(parent, YGEdgeTop);
		parent = YGNodeGetParent(parent);
	}
	this->pos = {x, y};
}

void Container::add_child(Container *cont) {
	YGNodeInsertChild(this->node, cont->node, this->children.size());
	this->children.push_back(cont);
}

const std::vector<Container *> Container::get_children() {
	return this->children;
}

void Container::set_border_percent(YGEdge edge, float value) {
	YGDirection direction = YGNodeLayoutGetDirection(this->node);
	switch (edge) {
	case YGEdgeAll:
		this->border_top = value;
		this->border_bottom = value;
		this->border_left = value;
		this->border_right = value;
		break;
	case YGEdgeTop:
		this->border_top = value;
		break;
	case YGEdgeBottom:
		this->border_bottom = value;
		break;
	case YGEdgeLeft:
		this->border_left = value;
		break;
	case YGEdgeRight:
		this->border_right = value;
		break;
	case YGEdgeStart:
		if (direction == YGDirectionLTR) {
			this->border_left = value;
		} else if (direction == YGDirectionRTL) {
			this->border_right = value;
		}
		break;
	case YGEdgeEnd:
		if (direction == YGDirectionLTR) {
			this->border_right = value;
		} else if (direction == YGDirectionRTL) {
			this->border_left = value;
		}
		break;
	case YGEdgeHorizontal:
		this->border_left = value;
		this->border_right = value;
		break;
	case YGEdgeVertical:
		this->border_top = value;
		this->border_bottom = value;
		break;
	}
}
void Container::set_border_max_px(YGEdge edge, float value) {
	YGDirection direction = YGNodeLayoutGetDirection(this->node);
	switch (edge) {
	case YGEdgeAll:
		this->border_top_max = value;
		this->border_bottom_max = value;
		this->border_left_max = value;
		this->border_right_max = value;
		break;
	case YGEdgeTop:
		this->border_top_max = value;
		break;
	case YGEdgeBottom:
		this->border_bottom_max = value;
		break;
	case YGEdgeLeft:
		this->border_left_max = value;
		break;
	case YGEdgeRight:
		this->border_right_max = value;
		break;
	case YGEdgeStart:
		if (direction == YGDirectionLTR) {
			this->border_left_max = value;
		} else if (direction == YGDirectionRTL) {
			this->border_right_max = value;
		}
		break;
	case YGEdgeEnd:
		if (direction == YGDirectionLTR) {
			this->border_right_max = value;
		} else if (direction == YGDirectionRTL) {
			this->border_left_max = value;
		}
		break;
	case YGEdgeHorizontal:
		this->border_left_max = value;
		this->border_right_max = value;
		break;
	case YGEdgeVertical:
		this->border_top_max = value;
		this->border_bottom_max = value;
		break;
	}
}

void Container::set_border_min_px(YGEdge edge, float value) {
	YGDirection direction = YGNodeLayoutGetDirection(this->node);
	switch (edge) {
	case YGEdgeAll:
		this->border_top_min = value;
		this->border_bottom_min = value;
		this->border_left_min = value;
		this->border_right_min = value;
		break;
	case YGEdgeTop:
		this->border_top_min = value;
		break;
	case YGEdgeBottom:
		this->border_bottom_min = value;
		break;
	case YGEdgeLeft:
		this->border_left_min = value;
		break;
	case YGEdgeRight:
		this->border_right_min = value;
		break;
	case YGEdgeStart:
		if (direction == YGDirectionLTR) {
			this->border_left_min = value;
		} else if (direction == YGDirectionRTL) {
			this->border_right_min = value;
		}
		break;
	case YGEdgeEnd:
		if (direction == YGDirectionLTR) {
			this->border_right_min = value;
		} else if (direction == YGDirectionRTL) {
			this->border_left_min = value;
		}
		break;
	case YGEdgeHorizontal:
		this->border_left_min = value;
		this->border_right_min = value;
		break;
	case YGEdgeVertical:
		this->border_top_min = value;
		this->border_bottom_min = value;
		break;
	}
}
