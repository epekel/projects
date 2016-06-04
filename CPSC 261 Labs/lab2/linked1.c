/*
* Includes.
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "linked-list.h"

/*
* Function to create a new list.
*
* Parameters:
*     none
* Returns:
*     a pointer to the head node for a new list.
*/
struct s_node *create_list()
{
	struct s_node *head = malloc(sizeof(struct s_node));
	head->value = 0;
	head->next = NULL;

	return head;
}

/*
* Function to print every element of the list.
*
* Parameters:
*     a pointer to the head node of the list.
* Returns:
*     nothing, but prints out the list elements.
*/
void print(struct s_node *head)
{
	struct s_node *node = head->next;
	while (node != NULL)
	{
		printf("Element: %ld\n", node->value);
		node = node->next;
	}
}

/*
* Function to insert an element at the front in the list.
*
* Parameters:
*     a pointer to the head node of the list.
*     the new value to insert.
*
* Returns:
*     nothing, but inserts the element at the front of the list.
*/
void insert_front(struct s_node *head, long value)
{
	struct s_node *new_node = malloc(sizeof(struct s_node));
	new_node->next = head->next;
	new_node->value = value;
	head->next = new_node;
	head->value++;
}

/*
* Function to print every element of the list, with positions.
*
* Parameters:
*     a pointer to the head node of the list.
* Returns:
*     nothing, but prints out the list elements with their positions.
*/
void print_with_positions(struct s_node *head)
{
	struct s_node *node = head->next;
	int position = 0;
	while (node != NULL) {
		printf("Element %ld at position %ld\n", node->value, position);
		node = node->next;
		position++;
	}
}

/*
* Function to retrieve the element at the position specified.
*
* Parameters:
*     a pointer to the head node of the list.
*     the position of the element to retrieve.
*
* Returns:
*     the element at the given position in the list, or the constant LLONG_MIN
*     if the position is out of range.
*/
long get_element_at(struct s_node *head, int position)
{
	int i;
	struct s_node *node = head->next;
	if (position < 0 || (long)position >= head->value) {
		return LONG_MIN;
	}
	else if (position == 0) {
		return node->value;
	}

	for (i = 1; i <= position; i++) {
		node = node->next;
	}
	return node->value;
}

/*
* Function to delete a list and free all of its nodes.
*
* Parameters:
*     a pointer to the head node of the list.
* Returns:
*     nothing.
*/
void free_list(struct s_node *head)
{
	long size = head->value;
	int i;
	struct s_node *node;
	node = head;
	for (i = 0; i <= size; i++) {
		node = node->next;
		free(head);
		head = node;
	}
}

/*
* Function to insert a new element at given position.
*
* Parameters:
*     a pointer to the head node of the list.
*     the position the new element should occupy.
*     the value of the new element.
* Returns
*     1 if successful, 0 if the position is invalid.
*/
int insert_at(struct s_node *head, int position, long value)
{
	// struct s_node *new_node = malloc(sizeof(struct s_node));
	insert_front(head, value);
	struct s_node *node = head->next;
	struct s_node *other = node->next;
	int i;
	//long shiftValue = 0;
	long copy;
	//node = head;
	if (position < 0 || position > head->value) { //buyuk esittirdi 
		return 0;
	}

	copy = node->value;
	for (i = 0; i <= position; i++) {
		if (i < position) {
			node->value = other->value;
			node = node->next;
			other = other->next;
		}
		else {
			node->value = copy;
		}
	}


	/* for (i = 0; i < head->value; i++) {
	if ((long)i < position) {
	node = node->next;
	}
	else if ((long)i == position) {
	new_node = node->next;
	shiftValue = new_node->value;
	new_node->value = value;
	node = node->next;
	head->value++;
	}
	else {
	node = node->next;
	copy = node->value;
	node->value = shiftValue;
	shiftValue = copy;
	/*new_node->value = node->value;
	node = node->next;
	}
	}*/
	return 1;
}

/*
* Function to insert a list inside another list. The list being inserted
* becomes part of the other list, and its head node is free()'d.
*
* Parameters:
*     a pointer to the head node of the target list.
*     the position of the first element of the inserted list should occupy.
*     a pointer to the head node of the list to insert.
* Returns
*     1 if successful, 0 if the position is invalid.
*/
int insert_list_at(struct s_node *head, int position, struct s_node *other_head)
{
	struct s_node *node = head->next;
	//struct s_node *node;
	//node = head;
	struct s_node *other_node = other_head->next;
	struct s_node *last_node;
	//struct s_node *new_node = malloc(sizeof(other_size * struct s_node));
	int other_size = other_head->value;
	int size = head->value;
	int i, j, k, loop;
	long nodeVal, newVal;
	if (position < 0 || position > size) {
		return 0;
	}
	/*for (i = 0; i < other_size; i++) {
	temp = temp->next;
	}
	for (j = 0; j <= position; j++) {
	node = node->next;
	}

	//node = other_head->next;
	//temp = node->next;
	//struct s_node *new_node = malloc(sizeof(other_size * struct s_node));*/

	//loop = other_size;
	head->value += other_head->value;

	for (i = 0; i < position; i++) {
		node = node->next;
	}
	last_node = node->next;
	node->next = other_node;
	free(other_head);
	for (j = 0; j < other_size; j++) {
		/*new_node->next = node->next;
		new_node->value = other_node->value;
		node->next = new_node;*/
		other_node = other_node->next;
	}
	other_node->next = last_node;
	//free(other_head);

	return 1;
}

/*
* Function to extract a sublist located inside another list. The extracted
* list is no longer part of the other list, and gets its own head node.
*
* Parameters:
*     a pointer to the head node of the target list.
*     the position of the first element of the list to extract.
*     the number of elements to extract
*
* Returns
*     the head node of the sublist if successful, NULL if the position or
*     number of elements to extract are invalid.
*/
struct s_node *extract_sublist(struct s_node *head, int position, int nb_of_elements)
{
	/* TO BE COMPLETED BY THE STUDENT. */
	return NULL;
}
