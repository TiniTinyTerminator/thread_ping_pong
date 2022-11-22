/**
 * @file main.c
 * @author Max Bensink (maxbensink@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>

sem_t sem_ping, sem_pong;

int32_t start, end;

void *ping(void *arg)
{

    while (start != end)
    {
        sem_wait(&sem_ping);

        printf("ping: %d\n", start);

        sem_post(&sem_pong);
    }
    
}

void *pong(void *arg)
{

    while (start != end)
    {
        sem_wait(&sem_pong);

        printf("pong: %d\n", start++);

        sem_post(&sem_ping);
    }
    

}

int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        printf("need at least a starting and ending value");

        exit(EXIT_FAILURE);
    }

    start = atoi(argv[1]);
    end = atoi(argv[2]);

    if (start > end)
    {
        printf("start needs to be lower that end");

        exit(EXIT_FAILURE);
    }

    pthread_t t1, t2;

    sem_init(&sem_ping, 0, 0);
    sem_init(&sem_pong, 0, 1);

    if (pthread_create(&t1, NULL, ping, NULL))
    {
        printf("couldn't initialize t1\n\r");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&t2, NULL, pong, NULL))
    {
        printf("couldn't initialize t1\n\r");
        exit(EXIT_FAILURE);
    }


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem_ping);
    sem_destroy(&sem_pong);

    return 0;
}
