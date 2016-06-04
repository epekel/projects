#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define VERBOSE 1
#define MAX_THINKING_TIME 25000

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
	if (forks[i].free == 1) {
		pthread_mutex_lock(&forks[i].lock);
		forks[i].free = 0;
		return 1;
	}
	else {
		pthread_cond_wait(&forks[i].forfree, &forks[i].lock);
	}
	return 0;
}

void putfork(long i)
{
	//pthread_mutex_unlock(&forks[i].lock);
	forks[i].free = 1;
	pthread_cond_signal(&forks[i].forfree);
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
	int leftF = leftfork(id);
	int rightF = rightfork(id);
	int first, second;
	int confirmR, confirmL;
	int random;

    while (meals < num_meals)
    {
		nap();
		if (rand() % 2 == 1) {
			first = rightF;
			second = leftF;
		}
		else {
			first = leftF;
			second = rightF;
		}
		confirmR = getfork((long)first);
		if (confirmR) {
			nap();
			if (VERBOSE) {
				printf("Philosopher %ld picked up a fork at random.\n", id);
			}
		}
		confirmL = getfork((long)second);
		if (confirmL) {
			nap();
			if (VERBOSE) {
				printf("Philosopher %ld picked up a fork at random.\n", id);
			}
		}
		if (confirmR && confirmL) {
			nap();
			meals++;
			if (VERBOSE) {
				printf("Philosopher %ld is eating.\n", id);
			}
			putfork((long)first);
			putfork((long)second);
			if (VERBOSE) {
				printf("Philosopher %ld put down the forks\n", id);
			}
			nap();
		}
		else {
			if (forks[first].free == 0) {
				putfork((long)first);
			}
			if (forks[second].free == 0) {
				putfork((long)second);
			}
			if (VERBOSE) {
				printf("Philosopher %ld put down whatever fork he had\n", id);
			}
			nap();
		}
		if (meals == num_meals) {
			pthread_exit(0);
			if (VERBOSE) {
				printf("Philosopher %ld exited\n", id);
			}
		}
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
