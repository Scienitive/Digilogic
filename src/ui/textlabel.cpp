#include "textlabel.hpp"
#include "container.hpp"
#include "yoga/YGNodeStyle.h"
#include <raylib.h>
#include <string>

TextLabel::TextLabel(std::string t)
	: text(t), font_name("fonts/JetBrainsMono-Regular.ttf"), font_size(12), spacing(1), text_color(BLACK) {
	YGNodeStyleSetWidthPercent(this->node, 100);
	YGNodeStyleSetHeightPercent(this->node, 100);
	this->font = new FontBank(); // BURAYI SIL
}

TextLabel::~TextLabel() {}

void TextLabel::draw() {
	Container::draw();
	Vector2 pos = this->get_screen_pos();
	DrawTextEx(this->get_font(), this->text.c_str(), pos, this->font_size, this->spacing, this->text_color);
}

float TextLabel::set_size_from_height(float height) {
	Vector2 measure_12 = MeasureTextEx(this->get_font(), this->text.c_str(), 12, this->spacing);
	Vector2 measure_13 = MeasureTextEx(this->get_font(), this->text.c_str(), 13, this->spacing);

	float diff = measure_13.y - measure_12.y;
	float diff_multiplier = (height - measure_12.y) / diff;
	this->font_size = measure_12.y + (diff_multiplier * diff);

	Vector2 measure = MeasureTextEx(this->get_font(), this->text.c_str(), this->font_size, this->spacing);
	YGNodeStyleSetHeight(this->node, measure.y);
	YGNodeStyleSetWidth(this->node, measure.x);
	return measure.x;
}

Font TextLabel::get_font() {
	return this->font->get_font(this->font_name, this->font_size);
}
