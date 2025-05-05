#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 // Number of philosophers

sem_t forks[N]; // Semaphores representing forks
pthread_t philosophers[N];

void *philosopher(void *num) {
    int id = *(int *)num;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        printf("Philosopher %d is hungry.\n", id);

        // Deadlock prevention: last philosopher picks right fork first
        if (id == N - 1) {
            sem_wait(&forks[right]);
            sem_wait(&forks[left]);
        } else {
            sem_wait(&forks[left]);
            sem_wait(&forks[right]);
        }

        printf("Philosopher %d is eating.\n", id);
        sleep(2);

        // Put down forks
        sem_post(&forks[left]);
        sem_post(&forks[right]);
    }
}

int main() {
    int i;
    int ids[N];

    // Initialize semaphores
    for (i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // Create philosopher threads
    for (i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join philosopher threads (this won't happen as they run indefinitely)
    for (i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores
    for (i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
