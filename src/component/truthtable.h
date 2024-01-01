#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

#include "state.h"
#include <stdbool.h>
#include <stddef.h>

// output is only valid when the left and right nodes are NULL
typedef struct TruthTableNode {
	struct TruthTableNode *left;
	struct TruthTableNode *right;
	State *output;
} TruthTableNode;

void fill_table(TruthTableNode *node, size_t depth);
TruthTableNode *create_truthtable(size_t depth);

#endif
