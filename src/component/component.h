#ifndef COMPONENT_H
#define COMPONENT_H

#include "state.h"
#include "truthtable.h"
#include <stddef.h>

typedef struct Component {
	const char *name;

	size_t input_count;
	State *input;
	size_t output_count;
	State *output;

	TruthTableNode *truth_table;
} Component;

#endif
