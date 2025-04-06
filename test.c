#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int buffer_size = 5;
int buffer[5];
int in = 0, out = 0;

sem_t empty,full;
pthread_mutex_t mutex;

void *producer(void *arg)
{
    int item;
    for(int i = 0; i<10; i++)
    {
        item = i;
        sem.wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % buffer_size;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

    }
    return NULL;
}

void *consumer(void *arg)
{
    int item;
    for(int i = 0; i<10; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % buffer_size;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

    }
    return NULL;
}

void main()
{
    pthread_t prod,cons;

    sem_init(&empty, 0, buffer_size);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
}