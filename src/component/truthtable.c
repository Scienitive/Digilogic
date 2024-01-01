#include "truthtable.h"
#include "../utils/utils.h"
#include <stddef.h>
#include <stdlib.h>

void fill_table(TruthTableNode *node, size_t depth) {
	node->left = malloc_or_die(sizeof(TruthTableNode));
	node->right = malloc_or_die(sizeof(TruthTableNode));
	node->left->output = NULL;
	node->right->output = NULL;
	if (depth - 1 > 0) {
		fill_table(node->left, depth - 1);
		fill_table(node->right, depth - 1);
	}
}

TruthTableNode *create_truthtable(size_t depth) {
	if (depth <= 0) {
		return NULL;
	}

	TruthTableNode *head = malloc_or_die(sizeof(TruthTableNode));
	head->output = NULL;
	fill_table(head, depth);
	return head;
}
