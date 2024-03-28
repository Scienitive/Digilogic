#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <raylib.h>
#include <tuple>
#include <vector>
#include <yoga/Yoga.h>

struct Container {
	YGNodeRef node;
	Color color;
	Vector2 pos;
	bool hovered;

	std::vector<Container *> children;

	// Border Percentage
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

	// Gap Percentage
	float gap_row;
	float gap_column;
	float gap_row_max;
	float gap_row_min;
	float gap_column_max;
	float gap_column_min;

public:
	Container();
	virtual ~Container();

	void add_child(Container *cont);
	const std::vector<Container *> get_children();

	void set_hovered();
	bool am_i_child_of_this(Container *cont);

	void set_screen_pos();

	// These are something I implemented because there is no YGNodeStyleSetBorderPercent
	void set_border_percent(YGEdge edge, float value);
	void set_border_max_px(YGEdge edge, float value);
	void set_border_min_px(YGEdge edge, float value);
	std::tuple<float, float, float> get_border_top();
	std::tuple<float, float, float> get_border_bottom();
	std::tuple<float, float, float> get_border_left();
	std::tuple<float, float, float> get_border_right();

	// These are something I implemented because there is no YGNodeStyleSetGapPercent
	void set_gap_percent(YGGutter axis, float value);
	void set_gap_max_px(YGGutter axis, float value);
	void set_gap_min_px(YGGutter axis, float value);
	std::tuple<float, float, float> get_gap_row();
	std::tuple<float, float, float> get_gap_column();

	virtual void early_step();
	virtual void step();
	virtual void draw();
	virtual void late_step();
};

#endif
