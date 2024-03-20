#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <raylib.h>
#include <vector>
#include <yoga/Yoga.h>

struct Container {
	YGNodeRef node;
	Color color;
	Vector2 pos;
	bool hovered;

	float border_top;
	float border_bottom;
	float border_left;
	float border_right;
	float border_top_max;
	float border_top_min;
	float border_bottom_max;
	float border_bottom_min;
	float border_left_max;
	float border_left_min;
	float border_right_max;
	float border_right_min;

private:
	std::vector<Container *> children;

public:
	Container();
	virtual ~Container();

	void add_child(Container *cont);
	const std::vector<Container *> get_children();

	void set_hovered();
	bool am_i_child_of_this(Container *cont);

	void set_screen_pos();

	// This is something I implemented because there is no YGNodeStyleSetBorderPercent
	void set_border_percent(YGEdge edge, float value);
	void set_border_max_px(YGEdge edge, float value);
	void set_border_min_px(YGEdge edge, float value);

	virtual void step();
	virtual void draw();
	virtual void late_step();
};

#endif
