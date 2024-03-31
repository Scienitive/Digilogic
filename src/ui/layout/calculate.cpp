#include "layout.hpp"
#include "raylib.h"

float LValue::get_pixel_value(float base) {
	if (this->type == Pixel) {
		return this->value;
	} else {
		return base / 100 * this->value;
	}
}

float LClamp::get_pixel_value(float base) {
	float value = this->value.get_pixel_value(base);
	float min = this->min.get_pixel_value(base);
	float max = this->max.get_pixel_value(base);

	if (value < min) {
		return min;
	} else if (value > max) {
		return max;
	}
	return value;
}

void Layout::calculate_width_height() {
	if (this->parent == nullptr) {
		this->c_width = this->width.get_pixel_value(GetScreenWidth());
		this->c_height = this->height.get_pixel_value(GetScreenHeight());
	} else {
		this->c_width = this->width.get_pixel_value(this->parent->c_width);
		this->c_height = this->height.get_pixel_value(this->parent->c_height);
	}
}

void Layout::calculate_padding() {
	this->c_padding_left = this->padding.left.get_pixel_value(this->c_width);
	this->c_padding_right = this->padding.right.get_pixel_value(this->c_width);
	this->c_padding_top = this->padding.top.get_pixel_value(this->c_width);
	this->c_padding_bottom = this->padding.bottom.get_pixel_value(this->c_width);
}

void Layout::calculate_margin() {
	this->c_margin_left = this->margin.left.get_pixel_value(this->c_width);
	this->c_margin_right = this->margin.right.get_pixel_value(this->c_width);
	this->c_margin_top = this->margin.top.get_pixel_value(this->c_width);
	this->c_margin_bottom = this->margin.bottom.get_pixel_value(this->c_width);
}

void Layout::calculate() {
	this->calculate_width_height();
	this->calculate_padding();
	this->calculate_margin();
}
