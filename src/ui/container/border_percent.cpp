#include "container.hpp"

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
