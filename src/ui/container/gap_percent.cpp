#include "container.hpp"
#include <tuple>

void Container::set_gap_percent(YGGutter axis, float value) {
	switch (axis) {
	case YGGutterRow:
		this->gap_row = value;
		break;
	case YGGutterColumn:
		this->gap_column = value;
		break;
	case YGGutterAll:
		this->gap_row = value;
		this->gap_column = value;
		break;
	}
}

void Container::set_gap_max_px(YGGutter axis, float value) {
	switch (axis) {
	case YGGutterRow:
		this->gap_row_max = value;
		break;
	case YGGutterColumn:
		this->gap_column_max = value;
		break;
	case YGGutterAll:
		this->gap_row_max = value;
		this->gap_column_max = value;
		break;
	}
}

void Container::set_gap_min_px(YGGutter axis, float value) {
	switch (axis) {
	case YGGutterRow:
		this->gap_row_min = value;
		break;
	case YGGutterColumn:
		this->gap_column_min = value;
		break;
	case YGGutterAll:
		this->gap_row_min = value;
		this->gap_column_min = value;
		break;
	}
}

std::tuple<float, float, float> Container::get_gap_row() {
	return std::make_tuple(this->gap_row, this->gap_row_max, this->gap_row_min);
}

std::tuple<float, float, float> Container::get_gap_column() {
	return std::make_tuple(this->gap_column, this->gap_column_max, this->gap_column_min);
}
