#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <raylib.h>
#include <string>

#define FONT_MULTIPLIER 0.9
#define FONT_SPACING 1.5
#define BUTTON_WIDTH_GAP 16

class Button {
	std::string text;
	Vector2 pos;
	int height;
	Color color;
	bool hovered;

private:
	void set_hovered();

public:
	Button(std::string text, int height, Color color);

	void set_pos(Vector2 pos);
	int get_height();

	int get_width();

	void draw();
	void input_handler();
};

#endif
