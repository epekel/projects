#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "implicit.h"

/*
 * Determine whether or not a block is in use.
 */
static int block_is_in_use(char *block_start)
{
    return 1 & *((long *) block_start);
}

/*
 * Return the size of a block.
 */
static long get_block_size(char *block_start)
{
    return -8 & *((long *) block_start);
}

/*
 * Set the size of a block, and whether or not it is in use. Remember each block
 * has two copies of the header (one at each end).
 */
static void set_block_header(char *block_start, long block_size, int in_use)
{
    long header_value = block_size | in_use;
    *((long *) block_start) = header_value;
    *((long *) (block_start + (block_size - sizeof(long)) / sizeof(char))) = header_value;
}

/*
 * Create a heap that is "size" bytes large.
 */
heap *heap_create(long size, int search_alg)
{
    heap *h = malloc(sizeof(heap));

    h->size = size;
    h->start = malloc(size);
    h->search_alg = search_alg;
    
    h->next = h->start;
    set_block_header(h->start, size, 0);
    return h;
}

/*
 * Dispose of (free) the whole heap.
 */
void heap_dispose(heap *h)
{
    free(h->start);
    free(h);
}

/*
 * Find the start of the block, given a pointer to the payload.
 */
static char *get_block_start(char *payload)
{
    return payload - sizeof(long) / sizeof(char);
}

/*
 * Find the payload, given a pointer to the start of the block.
 */
static char *get_payload(char *block_start)
{
    return block_start + sizeof(long) / sizeof(char);
}

/*
 * Find the start of the next block.
 */
static char *get_next_block(char *block_start)
{
    return block_start + get_block_size(block_start) / sizeof(char);
}

/*
 * Find the start of the previous block.
 */
static char *get_previous_block(char *block_start)
{
	
	char *prev_block_foot = block_start - 8 / sizeof(char);
	long prev_size = get_block_size(prev_block_foot);
	
    return prev_block_foot - (prev_size + 8) / sizeof(char);
}

/*
 * Coalesce two consecutive free blocks. Return a pointer to the beginning
 * of the coalesced block.
 */
static char *coalesce(char *first_block_start, char *second_block_start)
{
	
	if (block_is_in_use(first_block_start) == 1 || block_is_in_use(second_block_start) == 1) {
		printf("At least one of the blocks is not free!\n");
		return NULL;
	}
	long first_size = get_block_size(first_block_start);
	long second_size = get_block_size(second_block_start);
	set_block_header(first_block_start, first_size + second_size, 0);

	return first_block_start;
}

/*
 * Determine whether or not the given block is at the front of the heap.
 */
static int is_first_block(heap *h, char *block_start)
{
    return block_start == h->start;
}

/*
 * Determine whether or not the given block is at the end of the heap.
 */
static int is_last_block(heap *h, char *block_start)
{
    return block_start + get_block_size(block_start) == h->start + h->size;
}

/*
 * Print the structure of the heap to the screen.
 */
void heap_print(heap *h)
{
	
	char *block_start = h->start;
	while (is_last_block(h, block_start) == 0) {
		printf("Block at address %lx \n", block_start);
		printf("\tSize: %ld\n", get_block_size(block_start));
		printf("\tIn use: ");
		if (block_is_in_use(block_start)) {
			printf("Yes\n");
		}
		else {
			printf("No\n");
		}
		block_start = get_next_block(block_start);
	}
	printf("Block at address %lx \n", block_start);
	printf("\tSize: %ld\n", get_block_size(block_start));
	printf("\tIn use: ");
	if (block_is_in_use(block_start)) {
		printf("Yes\n");
	}
	else {
		printf("No\n");
	}
}

/*
 * Determine the average size of a free block.
 */
long heap_find_avg_free_block_size(heap *h)
{
    
	char *block_start = h->start;
	long size = 0;
	long count = 0;
	while (is_last_block(h, block_start) == 0) {
		if (block_is_in_use(block_start) == 0) {
			size += get_block_size(block_start);
			count++;
		}
		block_start = get_next_block(block_start);
	}
	if (block_is_in_use(block_start) == 0) {
		size += get_block_size(block_start);
		count++;
	}
    return size/count;
}

/*
 * Free a block on the heap h. Beware of the case where the  heap uses
 * a next fit search strategy, and h->next is pointing to a block that
 * is to be coalesced.
 */
void heap_free(heap *h, char *payload)
{
	
	char *h_start = h->start;
	char *block_start = get_block_start(payload);
	char *next_block = get_next_block(block_start);
	h->start = block_start;
	free(h->start);
	free(payload);
	if (block_is_in_use(next_block) == 0) {
		coalesce(block_start, next_block);
	}
	h->start = h_start;
}

/*
 * Determine the size of the block we need to allocate given the size
 * the user requested. Don't forget we need space for the header  and
 * footer.
 */
static long get_size_to_allocate(long user_size)
{
	
	long size = 0;
	long remainder;
	user_size += 2*sizeof(long); //4 bytes header and 4 bytes footer OR 8 bytes each??
	size += user_size;
	remainder = size % 8;
    return size + (8-remainder);
}

/*
 * Turn a free block into one the user can utilize. Split the block if
 * it's more than twice as large or MAX_UNUSED_BYTES bytes larger than
 * needed.
 */
static void *prepare_block_for_use(char *block_start, long real_size)
{
	
	if (block_is_in_use(block_start) == 1) {
		printf("Error: Block is in use!\n");
		return NULL;
	}

	long block_size = get_block_size(block_start);
	char *split_start;
	if (block_size > 2 * real_size || block_size > real_size + MAX_UNUSED_BYTES) {
		set_block_header(block_start, real_size, 1);
		split_start = get_next_block(block_start);
		set_block_header(split_start, block_size - real_size, 0);
	}
    return get_payload(block_start);
}

/*
 * Malloc a block on the heap h, using first fit. Return NULL if no block
 * large enough to satisfy the request exits.
 */
static void *malloc_first_fit(heap *h, long user_size)
{
	
	char *block_start = h->start;
	long block_size = get_size_to_allocate(user_size);
	long total_size = get_block_size(block_start);

	while (total_size <= h->size) {
		if ((block_is_in_use(block_start) == 0) && (block_size <= get_block_size(block_start))) {
			char *payload = get_payload(block_start);
			return payload;
		}
		block_start = get_next_block(block_start);
		total_size += get_block_size(block_start);
	}
    return NULL;
}

/*
 * Malloc a block on the heap h, using best fit. Return NULL if no block
 * large enough to satisfy the request exits.
 */
static void *malloc_best_fit(heap *h, long user_size)
{
	
	long block_size;
	long difference = MAX_UNUSED_BYTES + 1;
	long size = get_size_to_allocate(user_size);
	char *block_start = h->start;
	char *free_block;
	long total_size = get_block_size(block_start);
	while (total_size <= h->size) {
		block_size = get_block_size(block_start);
		if (block_size - size < difference) {
			difference = block_size - size;
			free_block = block_start;
		}
		block_start = get_next_block(block_start);
		total_size += get_block_size(block_start);
	}
	if (difference == MAX_UNUSED_BYTES + 1) {
		return NULL;
	}
	else {
		return free_block;
	}
}

/*
 * Malloc a block on the heap h, using next fit. Return NULL if no block
 * large enough to satisfy the request exits.
 */
static void *malloc_next_fit(heap *h, long user_size)
{
	
	char *block_start = h->start;
	char *block_next = h->next;
	long block_size = get_size_to_allocate(user_size);
	long total_size = get_block_size(block_next);

	while (total_size <= h->size) {
		if ((block_is_in_use(block_next) == 0) && (block_size <= get_block_size(block_next))) {
			char *payload = get_payload(block_next);
			return payload;
		}
		else if ((block_is_in_use(block_start) == 0) && (block_size <= get_block_size(block_start))) {
			char *payload = get_payload(block_start);
			return payload;
		}
		block_start = get_next_block(block_start);
		block_next = get_previous_block(block_next);
		total_size += get_block_size(block_next) + get_block_size(block_start);
	}
    return NULL;
}

/*
 * Our implementation of malloc.
 */
void *heap_malloc(heap *h, long size)
{
    switch (h->search_alg)
    {
        case HEAP_FIRSTFIT: return malloc_first_fit(h, size);
	case HEAP_NEXTFIT : return malloc_next_fit(h, size);
	case HEAP_BESTFIT : return malloc_best_fit(h, size);
    }
    return NULL;
}

/*
* Test function for static functions.
*/
void test(heap *h) {
	printf("\nSize to allocate for malloc(21): %ld\n", get_size_to_allocate(21));
	char *block_start = h->start;
	while (block_is_in_use(block_start) == 1) {
		block_start = get_next_block(block_start);
	}
	prepare_block_for_use(block_start, 32);
	heap_print(h);
	block_start = h->start;
	block_start = get_next_block(block_start);
	block_start = get_previous_block(block_start);
	printf("\nPrevious block size: %ld\n", get_block_size(block_start));
}