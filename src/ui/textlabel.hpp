#ifndef TEXTLABEL_HPP
#define TEXTLABEL_HPP

#include "container.hpp"
#include <raylib.h>
#include <string>

struct TextLabel : public Container {
	const std::string text;
	Font font;
	float font_size;
	float spacing;
	Color text_color;

	TextLabel();
	TextLabel(std::string t);
	~TextLabel();

	void draw() override;
	float set_size_from_height(float height);
};

#endif
