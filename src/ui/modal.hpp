#ifndef MODAL_HPP
#define MODAL_HPP

#include "container.hpp"

struct Modal : public Container {
	bool active;

	const int MAX_WIDTH = 500;
	const int MAX_HEIGHT = 500;

	Modal();
	~Modal();

	void set_size(float width_percentage, float height_percentage);

	void step() override;
	void draw() override;
	void late_step() override;
};

#endif
