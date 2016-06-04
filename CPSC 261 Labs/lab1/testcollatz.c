/*============================================================================
  Name        : testcollatz.c
  Author      : Patrice Belleville
  Description : Test the correctness of an external collatz routine
  ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdlib.h>

extern long collatz(long a);

int main(int argc, char **argv)
{
    int fail = 0;
    
    if (collatz(1) != 0) {
	printf("collatz(1) bad: %ld\n", collatz(1));
	fail ++;
    }
    if (collatz(6) != 8) {
	printf("collatz(6) bad: %ld\n", collatz(6));
	fail ++;
    }
    if (collatz(19) != 20) {
	printf("collatz(19) bad: %ld\n", collatz(19));
	fail ++;
    }
    if (collatz(27) != 111) {
	printf("collatz(27) bad: %ld\n", collatz(27));
	fail ++;
    }
    if (fail == 0)
	printf("collatz works\n");
    return fail;
}

