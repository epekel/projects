#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
 * Two constants used within the threads.
 */
#define LIMIT  10
#define DELAY   1
#define DO_LOCK 1

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
    int i, num;
    if (argv[1])
    {
        num = atoi(argv[1]);
    } else {
        printf("Error, please specify the number of threads intended\nExiting...");
        return 0;
    }
    thread_data *data_set = calloc(num, sizeof(thread_data));
    for (i = 0; i < num; ++i)
    {
        data_set[i].id = i;
        data_set[i].message = "TicTacToe";
    }
    srandom(time(0));

    pthread_t *threads;
    threads = malloc(sizeof(pthread_t)*num);

    for (i = 0; i < num; ++i)
    {
        if(pthread_create(&threads[i], NULL, &thread_body, &data_set[i]))
        {
            printf("Could not create thread number %d\n", i);
        }
    }
    for (i = 0; i < num; ++i)
    {
        if(pthread_join(threads[i], NULL))
        {
            printf("Could not join thread %d\n", i);
        }
    }

    /*
     * Done.
     */
    return 0;
}

