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

	virtual void step();
	virtual void draw();
	virtual void late_step();
};

#endif
