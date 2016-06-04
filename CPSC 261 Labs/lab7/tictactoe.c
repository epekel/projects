#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
 * Two constants used within the threads.
 */
#define LIMIT  10
#define DELAY   1
#define DO_LOCK 0

/*
 * A print routine that uses synchronization to ensure that lines are
 * printed atomically. You do not need to worry about the implementation
 * of this function. We will discuss thread_mutex_t in class this week.
 */
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void synchronized_print(char *message)
{
    if (DO_LOCK)
    {
	pthread_mutex_lock(&lock);
    }
    while (*message)
    {
	putchar(*message++);
    }
    putchar('\n');
    if (DO_LOCK) 
    {
	pthread_mutex_unlock(&lock);
    }
}

/*
 * Struct that holds data passed to each thread.
 */
typedef struct thread_data
{
    long id;
    char *message;
} thread_data;

/*
 * A function thread_body() that is executed by each one of the
 * threads.
 */
void *thread_body(void *arg)
{
    long i;
    thread_data *data = arg;
    char *buffer = malloc(256);

    for (i = 0; i < LIMIT; ++i)
    {
	sprintf(buffer, "Thread %5ld says \"%s\" for the %ldth time", data->id, data->message, i);
	synchronized_print(buffer);
	usleep(random() % DELAY);
    }
    return 0;
}

/*
 * The main function: it starts the three threads.
 */
int main(int argc, char **argv)
{
    thread_data tic_data, tac_data, toe_data;
    srandom(time(0));

    /*
     * Initialize the data used by each thread.
     */
    tic_data.id = 0;
    tic_data.message = "Tic";

    tac_data.id = 1;
    tac_data.message = "Tac";

    toe_data.id = 2;
    toe_data.message = "Toe";

    pthread_t t1, t2, t3;

    if (pthread_create(&t1, NULL, &thread_body, &tic_data) || 
        pthread_create(&t2, NULL, &thread_body, &tac_data) || 
        pthread_create(&t3, NULL, &thread_body, &toe_data))
    {
        printf("Could not create threads\n");
    }

    if (pthread_join(t1, NULL)) 
    printf("Could not join thread 1\n");
    if (pthread_join(t2, NULL)) 
    printf("Could not join thread 2\n");
    if (pthread_join(t3, NULL)) 
    printf("Could not join thread 3\n");

    /*
     * Done.
     */
    return 0;
}

