#ifndef TEXTLABEL_HPP
#define TEXTLABEL_HPP

#include "../container/container.hpp"
#include <raylib.h>
#include <string>

struct TextLabel : public Container {
	const std::string text;
	std::string font_name;
	float font_size;
	float spacing;
	Color text_color;

	TextLabel(std::string t);
	~TextLabel();

	void draw() override;
	float set_font_size();
	Font get_font();
	Font get_font(float font_size);
};

#endif
