#include <stdio.h>

typedef long valuetype;

typedef struct tree_node
{		
    valuetype value; 
    struct tree_node *left;
    struct tree_node *right;
} tree_node; 

/*
 * Functions to make a tree_node.
 */
tree_node *make_random_tree_node (unsigned long n_nodes);
tree_node *make_complete_tree_node (unsigned long levels);
tree_node *make_little_tree_node (void);
tree_node *make_tree_node(int argc, char **argv);

void print_tree_node (tree_node* t); 
void show_tree_node (tree_node* t); 
long tree_height(tree_node *t);
long tree_nodes(tree_node *t);

/*
 * Function to read/write a tree from/to a file.
 */
tree_node *read_tree(FILE *file, int swap);
tree_node *read_tree_node(FILE *file, int swap);
void write_tree_node(FILE *file, tree_node* t);
void write_tree(FILE *file, tree_node* t);
