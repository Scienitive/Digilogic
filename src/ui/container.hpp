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
	~Container();

	void add_child(Container *cont);

	void draw();
};

#endif
