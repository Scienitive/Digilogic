#ifndef TEXTLABEL_HPP
#define TEXTLABEL_HPP

#include "../fontbank.hpp"
#include "container.hpp"
#include <raylib.h>
#include <string>

struct TextLabel : public Container {
	FontBank *font;

	const std::string text;
	std::string font_name;
	float font_size;
	float spacing;
	Color text_color;

	TextLabel(std::string t);
	~TextLabel();

	void draw() override;
	/* float set_size_from_height(float height); */
	float set_font_size();
	/* void set_font_size(float height); */
	Font get_font();
	Font get_font(float font_size);
};

#endif
