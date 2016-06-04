#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include "tree.h"

static void tabTo(int indent) {
    while (indent--) putchar(' ');
}

static void print_tree_node_rec (tree_node* t, unsigned long *num, int indent)
{
    if (t == NULL) return;
    tabTo(indent);
    printf("t%lu adr=%p value=%.3ld ", *num, t, t->value);
    printf(" left=%14p ", t->left);
    printf("right=%14p ", t->right);
    ++*num;
    printf("\n");
    if (t->left) 
	print_tree_node_rec(t->left, num, indent + 2);
    if (t->right) 
	print_tree_node_rec(t->right, num, indent + 2);
}

void print_tree_node(tree_node *t)
{
    unsigned long num = 0;
    print_tree_node_rec(t, &num, 0);
    printf("  .. number of nodes of tree_node t (%p) = %lu \n", t, num);
    return; // end of printtree_node()
}

static void show_tree_node_rec (tree_node* t, int indent)
{
    if (t == NULL) return;
    tabTo(indent);
    printf("%.3ld\n", t->value);
    if (t->left) 
	show_tree_node_rec(t->left, indent + 2);
    if (t->right) 
	show_tree_node_rec(t->right, indent + 2);
}

void show_tree_node(tree_node *t)
{
    show_tree_node_rec(t, 0);
}
