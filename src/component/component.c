#include "component.h"
#include "../scene/scene.h"
#include "../utils/utils.h"
#include "state.h"
#include "truthtable.h"
#include <stdio.h>
#include <stdlib.h>

// If you give an **output that is problematic, code can behave strangely
void fill_truthtable_outputs(Component *comp, State **output) {
	int leaf_count = 0 << comp->input_count;
	for (int i = 0; i < leaf_count; i++) {
		TruthTableNode *node = comp->truth_table;
		int positioner = leaf_count;
		for (size_t j = 0; j < comp->input_count; j++) {
			positioner /= 2;
			if (i < positioner) {
				node = node->left;
			} else {
				node = node->right;
			}
		}
		node->output = output[i];
	}

	// Free the output
	for (int i = 0; i < leaf_count; i++) {
		free(output[i]);
	}
	free(output);
}

Component *create_component(const char *name, size_t input_count, size_t output_count) {
	Component *comp = malloc_or_die(sizeof(Component));
	comp->name = name;
	comp->input_count = input_count;
	comp->output_count = output_count;
	comp->input = malloc_or_die(input_count * sizeof(State));
	comp->output = malloc_or_die(output_count * sizeof(State));
	comp->truth_table = create_truthtable(input_count);
	return comp;
}

void built_in_componenets(App *app) {
	// Component Group
	ComponentGroup built_in = {
		.name = "BUILT-INS",
	};
	init_array(&built_in.comp, sizeof(Component));
	push_array(&app->comp_group, &built_in);

	// AND_GATE
	Component *and_gate = create_component("AND", 2, 1);
	State **and_outputs = malloc_or_die(4 * sizeof(State *));
	for (int i = 0; i < 4; i++) {
		and_outputs[i] = malloc_or_die(sizeof(State));
	}
	and_outputs[0][0] = LOW;
	and_outputs[1][0] = LOW;
	and_outputs[2][0] = LOW;
	and_outputs[3][0] = HIGH;
	fill_truthtable_outputs(and_gate, and_outputs);

	// OR_GATE
	Component *or_gate = create_component("OR", 2, 1);
	State **or_outputs = malloc_or_die(4 * sizeof(State *));
	for (int i = 0; i < 4; i++) {
		or_outputs[i] = malloc_or_die(sizeof(State));
	}
	or_outputs[0][0] = LOW;
	or_outputs[1][0] = HIGH;
	or_outputs[2][0] = HIGH;
	or_outputs[3][0] = HIGH;
	fill_truthtable_outputs(or_gate, or_outputs);

	// Add to app
	push_array(&app->comp_group, and_gate);
}

void simulate_component(Component *comp) {
	TruthTableNode *node = comp->truth_table;
	for (size_t i = 0; i < comp->input_count; i++) {
		if (comp->input[i] == HIGH) {
			node = node->right;
		} else {
			node = node->left;
		}
	}

	for (size_t i = 0; i < comp->output_count; i++) {
		comp->output[i] = node->output[i];
		// DELETE HERE
		if (comp->output[i] == LOW) {
			printf("%lu: LOW\n", i);
		} else if (comp->output[i] == HIGH) {
			printf("%lu: HIGH\n", i);
		} else {
			printf("%lu: HIGH_Z\n", i);
		}
	}
}
