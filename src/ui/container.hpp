#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <raylib.h>
#include <vector>
#include <yoga/Yoga.h>

struct Container {
	YGNodeRef node;
	Color color;

private:
	std::vector<Container *> children;

public:
	Container();
	virtual ~Container();

	void add_child(Container *cont);

	Vector2 get_screen_pos();
	virtual void draw();
};

#endif
