#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define VERBOSE 1
#define MAX_THINKING_TIME 50000

typedef struct fork
{
    pthread_mutex_t lock;
    pthread_cond_t forfree;
    long free;
} fork_t;

int num_phils, num_meals;    
fork_t *forks;

void nap()
{
    usleep(random() % MAX_THINKING_TIME);
}

void initfork(int i)
{
    pthread_mutex_init(&forks[i].lock, 0);
    pthread_cond_init(&forks[i].forfree, 0);
    forks[i].free = 1;
}
    
long getfork(long i)
{
    /* TO BE IMPLEMENTED BY THE STUDENTS. */
    return 1;
}

void putfork(long i)
{
    /* TO BE IMPLEMENTED BY THE STUDENTS. */
}

int leftfork(long i)
{
    return i;
}

int rightfork(long i)
{
    return (i + 1) % num_phils;
}

void *phil(void *arg)
{
    long id = (long) arg;
    int meals = 0;

    while (meals < num_meals)
    {
        /* TO BE IMPLEMENTED BY THE STUDENTS. */
    }
    return 0;
}

int main(int argc, char **argv)
{
    pthread_t *p;
    long i;

    if (argc != 3)
    {
	fprintf(stderr, "Usage: %s num_philosophers num_meals\n", argv[0]);
	return 1;
    }
    num_phils = strtol(argv[1], 0, 0);
    num_meals = strtol(argv[2], 0, 0);

    forks = malloc(num_phils * sizeof(fork_t));
    p = malloc(num_phils * sizeof(pthread_t));
    
    srandom(time(0));
    for (i = 0; i < num_phils; ++i)
    {
	initfork(i);
    }
    for (i = 0; i < num_phils; ++i)
    {
	if (pthread_create(&p[i], 0, phil, (void *) i))
        {
	    fprintf(stderr, "Unable to create thread for philosopher %ld\n", i);
	    exit(1);
	}
    }
    for (i = 0; i < num_phils; ++i)
    {
	if (pthread_join(p[i], 0))
        {
	    fprintf(stderr, "Unable to join thread for philosopher %ld\n", i);
	    exit(2);
	}
    }
    return 0;
}
