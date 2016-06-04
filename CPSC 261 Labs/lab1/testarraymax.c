/*
 ============================================================================
 Name        : Testarraymax.c
 Author      : Patrice Belleville
 Description : Test the correctness of an external arraymax function
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdlib.h>

extern long arraymax(long *p, long c);

long vals[] = { 3, 1, 8, 4, 9 };

int main(int argc, char **argv)
{
    int fail = 0;
    if (arraymax(vals, 0) != 0x8000000000000000) {
	printf("arraymax(vals, 0) bad: %ld\n", arraymax(vals, 0));
	fail ++;
    }
    if (arraymax(vals, 1) != 3) {
	printf("arraymax(vals, 1) bad: %ld\n", arraymax(vals, 1));
	fail ++;
    }
    if (arraymax(vals, 2) != 3) {
	printf("arraymax(vals, 2) bad: %ld\n", arraymax(vals, 2));
	fail ++;
    }
    if (arraymax(vals, 3) != 8) {
	printf("arraymax(vals, 3) bad: %ld\n", arraymax(vals, 3));
	fail ++;
    }
    if (arraymax(vals, 4) != 8) {
	printf("arraymax(vals, 4) bad: %ld\n", arraymax(vals, 4));
	fail ++;
    }
    if (arraymax(vals, 5) != 9) {
	printf("arraymax(vals, 5) bad: %ld\n", arraymax(vals, 5));
	fail ++;
    }
    if (fail == 0)
	printf("arraymax works\n");
    return fail;
}
