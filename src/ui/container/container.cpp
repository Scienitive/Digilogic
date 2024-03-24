#include "container.hpp"
#include "../modal/modal.hpp"
#include "../ui.hpp"
#include <raylib.h>
#include <vector>
#include <yoga/YGNode.h>
#include <yoga/YGNodeLayout.h>

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

void Container::early_step() {
	const std::vector<Container *> copy_children = this->children;
	for (Container *cont : copy_children) {
		cont->early_step();
	}
}

void Container::step() {
	UI &ui = UI::get();
	size_t active_modal_count = ui.active_modals.size();
	if (this == ui.containers.main || active_modal_count <= 0 || this == ui.active_modals[active_modal_count - 1] ||
		(this->am_i_child_of_this(ui.active_modals[active_modal_count - 1]))) {
		this->set_hovered();

		// The reason of copying here is: some functions can add to children vector and it causes segfaults
		const std::vector<Container *> copy_children = this->children;
		for (Container *cont : copy_children) {
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

	const std::vector<Container *> copy_children = this->children;
	for (Container *cont : copy_children) {
		Modal *modal = dynamic_cast<Modal *>(cont);
		if (modal == nullptr) {
			cont->draw();
		}
	}
}

void Container::late_step() {
	const std::vector<Container *> copy_children = this->children;
	for (Container *cont : copy_children) {
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
