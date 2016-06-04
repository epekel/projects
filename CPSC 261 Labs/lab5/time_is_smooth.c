/*
 ============================================================================
 Name        : timeissmooth.c
 Author      : Patrice Belleville
 Description : Time the is_smooth function
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdlib.h>

static struct timeval start_ts, end_ts, diff_ts;

void startClock() {
    gettimeofday(&start_ts, 0);
}

void endClock() {
    gettimeofday(&end_ts, 0);
}

struct timeval timeminus(struct timeval a, struct timeval b)
{
    struct timeval res;
    res.tv_sec = a.tv_sec - b.tv_sec;
    if (a.tv_usec > b.tv_usec) {
	res.tv_usec = a.tv_usec - b.tv_usec;
    } else {
	res.tv_usec = 1000000 + a.tv_usec - b.tv_usec;
	res.tv_sec--;
    }
    return res;
}

long usecClock() {
    diff_ts = timeminus(end_ts, start_ts);
    return diff_ts.tv_usec + 1000000 * diff_ts.tv_sec;
}

int longLess(const void *a, const void *b) {
    return *(long *)a - *(long *)b;
}

extern int is_smooth(long *array, long size);

/*
 * Generate a random smooth array with "size" elements.
 */
static void generate_smooth_array(long *array, long size)
{
    long i;
    
    array[0] = 1000;
    for (i = 1; i < size; i++)
    {
        array[i] = array[i-1] + random() % 5 - 2;
    }
}

/*
 * Make sure your function is able to detect non-smooth arrays.
 */
long check_correctness(long *array, long size, int first, int second, int diff)
{
    int x = array[first];
    int result;
    
    array[first] = array[second] + diff;
    result = is_smooth(array, size);
    array[first] = x;

    return result;
}

int main(int argc, char **argv)
{
    long l, limit = 5000, size = 1000000;
    long *p = calloc(size, sizeof(long));
    volatile long x;
    
    generate_smooth_array(p, size);

    /*
    ** Check to make sure the is_smooth() function returns the correct value.
    */
    x = check_correctness(p, size, 0, 1, 3)     + check_correctness(p, size, 0, 1, -3)     +
        check_correctness(p, size, 99, 100, 3)  + check_correctness(p, size, 99, 100, -3)  + 
        check_correctness(p, size, 100, 101, 3) + check_correctness(p, size, 100, 101, -3) + 
        check_correctness(p, size, size-1, size-2, 3) + check_correctness(p, size, size-1, size-2, -3);

    if (! is_smooth(p, size) || x > 0)
    {
        puts("Your is_smooth() function did not return the correct answer\n");
    }

    /*
     * Now time "limit" iterations of the function on a smooth array.
     */
    printf("Timing smooth\n");
    startClock();
    for (l = 0; l < limit; ++l) {
	x += is_smooth(p, size);
    }
    endClock();
	
    printf("%ld invocations of is_smooth(%ld) took: %ld usec\n", limit, size, usecClock());
    return 0;
}
