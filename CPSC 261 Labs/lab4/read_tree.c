#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "endian.h"

#define TABLESIZE 1000000

struct {
	long id;
	tree_node *tree;
} lookupTable[TABLESIZE];

int n_entries = 0;
long *buffer;

void remember_id(long id, tree_node *tree)
{
	lookupTable[n_entries].id = id;
	lookupTable[n_entries].tree = tree;
	n_entries++;
}

tree_node *find_node_with_id(long id)
{
	int i;
	for (i = 0; i < n_entries; ++i)
	{
		if (lookupTable[i].id == id)
		{
			return lookupTable[i].tree;
		}
	}
	return NULL;
}

tree_node *read_tree_node(FILE *file, int swap) {
	tree_node *node = malloc(sizeof(tree_node));
	long value, left, right;
	
	read_long(file, swap, buffer);
	node->value = *buffer;
	read_long(file, swap, buffer);
	node->left = (void *)*buffer;
	read_long(file, swap, buffer);
	node->right = (void *)*buffer;

	return node;
}

tree_node *read_tree(FILE *file, int swap) {
	buffer = malloc(sizeof(long));
	tree_node *node;
	long id;
	int i;
	//int root = 1;

	while (!feof(file)) {
		read_long(file, swap, buffer);
		id = *buffer;
		node = read_tree_node(file, swap);
		if (feof(file)) {
			break;
		}
		remember_id(id, node);
		printf("ID: %ld, Value: %ld, Left: %ld, Right: %ld\n", id, node->value, node->left, node->right);
	}

	for (i = 0; i < n_entries; i++) {
		//ptr = lookupTable[i].tree;
		if (lookupTable[i].tree->left != 0) {
			//leftId = (long)ptr->left;
			lookupTable[i].tree->left = find_node_with_id((long)lookupTable[i].tree->left);
		}
		if (lookupTable[i].tree->right != 0) {
			//rightId = (long)ptr->right;
			lookupTable[i].tree->right = find_node_with_id((long)lookupTable[i].tree->right);
		}
			
		/*if (root) {
			root--;
		}
		else {
			if (lookupTable[i].id == lookupTable[i - 1].tree->left) {
				lookupTable[i - 1].tree->left = lookupTable[i].tree;
			}
			else if (lookupTable[i].id == lookupTable[i - 1].tree->right) {
				lookupTable[i - 1].tree->right = lookupTable[i].tree;
			}
		}*/
	}

	return lookupTable[0].tree;
}
