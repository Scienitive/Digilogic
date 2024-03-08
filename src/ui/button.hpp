#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "textlabel.hpp"
#include <functional>
#include <raylib.h>

struct Button : public Container {
	TextLabel *text_label;

	Button(std::string text);
	~Button();

private:
	std::function<void()> on_click;
	bool old_hovered;

	void set_size_auto();

public:
	void step() override;
	void draw() override;
	void late_step() override;

	void set_on_click(std::function<void()> func);
};

#endif
