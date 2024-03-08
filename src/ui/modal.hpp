#ifndef MODAL_HPP
#define MODAL_HPP

#include "container.hpp"

struct Modal : public Container {
	const int MAX_WIDTH = 500;
	const int MAX_HEIGHT = 500;

private:
	bool active;

	float aspect_ratio;
	float height_percentage;
	float height_max_px;

public:
	Modal();
	~Modal();

	void set_size(float aspect_ratio, float height_percentage, float height_max_px);
	void calculate_layout();

	void step() override;
	void draw() override;
	void late_step() override;

	void activate();
	void deactivate();
	bool is_active();
};

#endif
