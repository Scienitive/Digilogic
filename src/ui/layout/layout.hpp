#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include <vector>

enum LType {
	LTypeFlex,
	LTypeAbsolute,
};

enum LPrimary {
	LPrimaryStart,
	LPrimaryCenter,
	LPrimaryEnd,
};

enum LSecondary {
	LSecondaryStart,
	LSecondaryCenter,
	LSecondaryEnd,
};

enum LEdge {
	LEdgeLeft,
	LEdgeRight,
	LEdgeTop,
	LEdgeBottom,
	LEdgeHorizontal,
	LEdgeVertical,
	LEdgeAll,
};

enum LGutter {
	LGutterPrimary,
	LGutterSecondary,
	LGutterAll,
};

enum LValueType {
	Pixel,
	Percentage,
};

struct LValue {
	LValueType type;
	float value;

	LValue() : type(Pixel), value(0) {}
	float get_pixel_value(float base);
};

struct LClamp {
	LValue value;
	LValue min;
	LValue max;

	float get_pixel_value(float base);
};

struct LDoublePos {
	LClamp primary;
	LClamp secondary;
};

struct LMultiPos {
	LClamp left;
	LClamp right;
	LClamp top;
	LClamp bottom;
};

class Layout {
	Layout *parent;
	std::vector<Layout> children;

	LType type;

	// Flex
	LPrimary primary;
	LSecondary secondary;
	bool grow;
	bool wrap;
	LDoublePos gap;

	// Absolute
	LValue left;
	LValue top;

	// General
	LClamp width;
	LClamp height;
	LMultiPos margin;
	/* LMultiPos border; */ // Disabled for now
	LMultiPos padding;

	// Calculated
	float c_width;
	float c_height;

	float c_margin_left;
	float c_margin_right;
	float c_margin_top;
	float c_margin_bottom;

	float c_padding_left;
	float c_padding_right;
	float c_padding_top;
	float c_padding_bottom;

	float c_gap_primary;
	float c_gap_secondary;

	float c_left;
	float c_right;

public:
	Layout();
	~Layout();

	void set_type(LType type);
	void set_primary(LPrimary value);
	void set_secondary(LSecondary value);
	void set_grow(bool value);
	void set_wrap(bool value);
	void set_gap(LGutter gutter, LValueType type, float value);
	void set_gap_min(LGutter gutter, LValueType type, float value);
	void set_gap_max(LGutter gutter, LValueType type, float value);

	void set_left(LValueType type, float value);
	void set_top(LValueType type, float value);

	void set_width(LValueType type, float value);
	void set_width_min(LValueType type, float value);
	void set_width_max(LValueType type, float value);
	void set_height(LValueType type, float value);
	void set_height_min(LValueType type, float value);
	void set_height_max(LValueType type, float value);
	void set_margin(LEdge edge, LValueType type, float value);
	void set_margin_min(LEdge edge, LValueType type, float value);
	void set_margin_max(LEdge edge, LValueType type, float value);
	void set_padding(LEdge edge, LValueType type, float value);
	void set_padding_min(LEdge edge, LValueType type, float value);
	void set_padding_max(LEdge edge, LValueType type, float value);

	Layout *get_parent();
	std::vector<Layout> &get_children();
	void add_child(Layout &&child);

	void calculate();

private:
	std::vector<LClamp> gap_gutter_helper(LGutter gutter);
	std::vector<LClamp> margin_edge_helper(LEdge edge);
	std::vector<LClamp> padding_edge_helper(LEdge edge);

	void calculate_width_height();
	void calculate_padding();
	void calculate_margin();
};

#endif
