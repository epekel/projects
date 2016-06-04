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
	struct s_node *new_node = malloc(sizeof(struct s_node));
	struct s_node *node = head->next;
	int i;
	if (position < 0 || position > head->value) {
		return 0;
	}
	for (i = 0; i < position-1; i++) {
		node = node->next;
	}
	if (position == 0) {
		new_node->next = node;
		head->next = new_node;
	}
	else {
		new_node->next = node->next;
		node->next = new_node;
	}
	new_node->value = value;
	head->value++;
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
	struct s_node *other_node = other_head->next;
	struct s_node *next_node; // list will be inserted between node and next_node
	int other_size = other_head->value;
	int size = head->value;
	int i, j;

	if (position < 0 || position > size) {
		return 0; // return 0 if position is invalid
	}
	
	head->value += other_head->value; // increase the size of the list to accommodate the changes

	for (i = 0; i < position - 1; i++) {
		node = node->next;
	}

	if (position == 0) {
		head->next = other_node;
		next_node = node;
	}
	else {
		node->next = other_node;
		next_node = node->next;
	}
	free(other_head);
	for (j = 0; j < other_size - 1; j++) {
		other_node = other_node->next;
	}
	other_node->next = next_node;

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
	struct s_node *node = head->next;
	struch s_node *other, *prev;
	struct s_node *extract_head = create_list();
	//struct s_node *extract_node = extract_head->next;
	int i, j;

	if (position < 0 || position >= head->value) {
		return NULL; // return NULL if position is invalid
	}
	else if (nb_of_elements <= 0 || nb_of_elements > head->value) {
		return NULL; // return NULL if number of elements is invalid
	}

	for (i = 0; i < position; i++) {
		if (i == position - 1) {
			prev = node;
		}
		node = node->next;
	}
	extract_head->next = node;
	for (j = 0; j < nb_of_elements; j++) {
		node = node->next;
		extract_head->value++;
	}
	other = node->next;
	node->next = NULL;
	prev->next = other;

	return extract_head;
}
