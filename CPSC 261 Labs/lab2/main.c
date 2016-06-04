#include <stdio.h>
#include "linked-list.h"

#define INITIAL_LENGTH 7
#define OTHER1_L 4
#define OTHER2_L 8
#define OTHER3_L 1
#define MAX_L 8

int main(int argc, char *argv[])
{
	int contents[INITIAL_LENGTH] = { 8, 5, -6, 13, -17, 4, 2 };
	int other1[OTHER1_L] = { 99, 88, 77, 66 };
	int other2[OTHER2_L] = { 99, 88, 77, 66, 55, 44, 33, 22 };
	int other3[OTHER3_L] = { 0 };
	int i, j;

	struct s_node *mylist = create_list();
	struct s_node *otherlist1 = create_list();
	struct s_node *otherlist2 = create_list();
	struct s_node *otherlist3 = create_list();

	for (i = 0; i < INITIAL_LENGTH; i++)
	{
		insert_front(mylist, contents[i]);
	}
	for (j = 0; j < MAX_L; j++)
	{
		if (j < OTHER1_L) {
			insert_front(otherlist1, other1[j]);
		}
		if (j < OTHER2_L) {
			insert_front(otherlist2, other2[j]);
		}
		if (j < OTHER3_L) {
			insert_front(otherlist3, other3[j]);
		}
	}

	print(mylist);
	printf("\n----------PRINT TEST DONE----------\n\n");
	print_with_positions(mylist);
	printf("\n----------PRINT_WITH_POSITIONS TEST DONE----------\n\n");

	long testGet1 = get_element_at(mylist, 3);
	long testGet2 = get_element_at(mylist, 7);
	long testGet3 = get_element_at(mylist, 0);
	printf("Result of the tests of get_element_at: %ld (pos: 3), %ld (pos: 7), and %ld (pos: 0)\n", testGet1, testGet2, testGet3);
	printf("\n----------GET_ELEMENT_AT TEST DONE----------\n\n");

	insert_at(mylist, 3, 0);
	printf("Inserted 0 at position 3:\n");
	print_with_positions(mylist);
	printf("\n");
	insert_at(mylist, 0, 28);
	printf("Inserted 28 at position 0:\n");
	print_with_positions(mylist);
	printf("\n");
	insert_at(mylist, INITIAL_LENGTH-1, -22);
	printf("Inserted -22 at position INITIAL_LENGTH-1:\n");
	print_with_positions(mylist);
	printf("\n");
	printf("\n----------INSERT_AT TEST DONE----------\n\n");

	print(mylist);
	printf("\n");
	print(otherlist1);
	printf("\nInserting otherlist1 at position 0\n");
	insert_list_at(mylist, 0, otherlist1);
	print_with_positions(mylist);

	printf("\n\n");
	print(mylist);
	printf("\n");
	print(otherlist2);
	printf("\nInserting otherlist2 at the end of mylist (pos: INITIAL_LENGTH + OTHER1_L)\n");
	insert_list_at(mylist, INITIAL_LENGTH+OTHER1_L, otherlist2);
	print_with_positions(mylist);

	printf("\n\n");
	print(mylist);
	printf("\n");
	print(otherlist3);
	printf("\nInserting otherlist3 at the position 5\n");
	insert_list_at(mylist, 5, otherlist3);
	print_with_positions(mylist);
	printf("\n----------INSERT_LIST_AT TEST DONE----------\n\n");

	free_list(mylist);
	printf("\nPrinting mylist to see if elements have random values (i.e. free()'d):\n");
	print(mylist);
	printf("\n----------FREE_LIST TEST DONE----------\n\n");

	printf("\n----------EXTRACT_SUBLIST TEST:----------\n\n");
	struct s_node *sublist = extract_sublist(mylist, 8, 6);
	printf("Sublist of 6 elements taken starting from position 8:\n");
	print(sublist);
}
