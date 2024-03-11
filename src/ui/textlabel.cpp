#include "textlabel.hpp"
#include "container.hpp"
#include "yoga/YGConfig.h"
#include "yoga/YGNode.h"
#include "yoga/YGNodeLayout.h"
#include "yoga/YGNodeStyle.h"
#include <iostream>
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
	this->set_screen_pos();
	DrawTextEx(this->get_font(), this->text.c_str(), this->pos, this->font_size, this->spacing, this->text_color);
}

// For button->text_labels generally
float TextLabel::set_size_from_height(float height) {
	this->set_font_size(height);

	Vector2 measure = MeasureTextEx(this->get_font(), this->text.c_str(), this->font_size, this->spacing);
	YGNodeStyleSetHeight(this->node, measure.y);
	YGNodeStyleSetWidth(this->node, measure.x);
	return measure.x;
}

// It calculates from height of the TextLabel container
void TextLabel::set_font_size() {
	float height = YGNodeLayoutGetHeight(this->node);
	Vector2 measure_12 = MeasureTextEx(this->get_font(), this->text.c_str(), 12, this->spacing);
	Vector2 measure_13 = MeasureTextEx(this->get_font(), this->text.c_str(), 13, this->spacing);

	float diff = measure_13.y - measure_12.y;
	float diff_multiplier = (height - measure_12.y) / diff;
	this->font_size = measure_12.y + (diff_multiplier * diff);

	// Also set width
	Vector2 measure = MeasureTextEx(this->get_font(), this->text.c_str(), this->font_size, this->spacing);
	YGNodeStyleSetWidth(this->node, measure.x);
}

void TextLabel::set_font_size(float height) {
	Vector2 measure_12 = MeasureTextEx(this->get_font(), this->text.c_str(), 12, this->spacing);
	Vector2 measure_13 = MeasureTextEx(this->get_font(), this->text.c_str(), 13, this->spacing);

	float diff = measure_13.y - measure_12.y;
	float diff_multiplier = (height - measure_12.y) / diff;
	this->font_size = measure_12.y + (diff_multiplier * diff);
}

Font TextLabel::get_font() {
	return this->font->get_font(this->font_name, this->font_size);
}
