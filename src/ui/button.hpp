#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "textlabel.hpp"
#include <functional>
#include <raylib.h>
#include <vector>

struct Button : public Container {
	TextLabel *text_label;

	float width;
	std::vector<Button *> width_linked_buttons;

	Button(std::string text);
	~Button();

private:
	std::function<void()> on_click;
	bool old_hovered;

public:
	void step() override;
	void draw() override;
	void late_step() override;

	void set_on_click(std::function<void()> func);
	void width_link_button(Button *other);
};

#endif
