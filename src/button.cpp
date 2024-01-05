#include "button.hpp"
#include <raylib.h>
#include <string>

Button::Button(std::string text, int height, Color color) : text(text), height(height), color(color), hovered(false) {}

void Button::set_pos(Vector2 pos) {
	this->pos = pos;
}

int Button::get_height() {
	return this->height;
}

int Button::get_width() {
	int font_size = this->height * FONT_MULTIPLIER;
	Vector2 text_dimensions = MeasureTextEx(GetFontDefault(), this->text.c_str(), font_size, FONT_SPACING);
	return (text_dimensions.x + BUTTON_WIDTH_GAP);
}

void Button::draw() {
	Color color;
	Vector2 size = {
		static_cast<float>(this->get_width()),
		static_cast<float>(this->height),
	};

	if (this->hovered) {
		color = ColorBrightness(this->color, -1);
	} else {
		color = this->color;
	}

	DrawRectangle(this->pos.x, this->pos.y, size.x, size.y, color);

	int font_size = this->height * FONT_MULTIPLIER;
	Vector2 text_dimensions = MeasureTextEx(GetFontDefault(), this->text.c_str(), font_size, FONT_SPACING);
	Vector2 text_pos = {
		static_cast<float>(this->pos.x + (BUTTON_WIDTH_GAP / 2.0f)),
		this->pos.y + (this->height - text_dimensions.y),
	};
	DrawTextEx(GetFontDefault(), this->text.c_str(), text_pos, font_size, FONT_SPACING, BLACK);
}

void Button::set_hovered() {
	Vector2 mouse_pos = GetMousePosition();
	if (mouse_pos.x >= this->pos.x && mouse_pos.x <= this->pos.x + this->get_width() && mouse_pos.y >= this->pos.y &&
		mouse_pos.y <= this->pos.y + this->height) {
		this->hovered = true;
	} else {
		this->hovered = false;
	}
}

void Button::input_handler() {
	this->set_hovered();
}
