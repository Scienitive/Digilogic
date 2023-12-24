#ifndef COMPONENT_H
#define COMPONENT_H

typedef enum State { LOW, HIGH, HIGH_Z } State;

typedef struct Component {
	const char *name;
	State *input;
	State *output;
} Component;

#endif
