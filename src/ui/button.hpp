#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "container.hpp"
#include "textlabel.hpp"
#include <raylib.h>

struct Button : public Container {
	TextLabel *text_label;

	Button(std::string text);
	~Button();

private:
	bool old_hovered;

	void set_size_auto();

public:
	void draw() override;
	void late_step() override;
};

#endif
