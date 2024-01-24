/*
  Project: Dining-Philosophers
  Author: Matthew Skovorodin
  Description: This C program tackles the Dining Philosophers problem using mutex variables and pthreads. The solution is designed for a Linux environment.
  */
#include "random.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

const char *philosopher_names[] = {"Descartes", "Socrates", "Diogenes", "Aristotle", "Plato"};
pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];
int think_time[NUM_PHILOSOPHERS] = {0};

// Structure to hold philosopher-specific information
struct PhilosopherArgs {
    int id;
};

// Function to let a philosopher take chopsticks
void take_chopsticks(int id) {
    pthread_mutex_lock(&chopsticks[id]);
    pthread_mutex_lock(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
    printf("%s is taking chopsticks %d and %d\n", philosopher_names[id], id, (id + 1) % NUM_PHILOSOPHERS);
}

// Function to put away chopsticks after eating
void put_away_chopsticks(int id) {
    pthread_mutex_unlock(&chopsticks[id]);
    pthread_mutex_unlock(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
    printf("%s is putting down chopsticks %d and %d\n", philosopher_names[id], id, (id + 1) % NUM_PHILOSOPHERS);
}

// Function for a philosopher to wait for chopsticks
void wait_for_chopsticks(int id) {
    printf("%s is waiting\n", philosopher_names[id]);
}

// Function for a philosopher to eat
void eat(int id) {
    printf("%s is eating\n", philosopher_names[id]);
    int time = randomGaussian(9, 3);
    if (time < 0) time = 0;
    sleep(time);
}

// Function for a philosopher to think
void think(int id) {
    printf("%s is thinking\n", philosopher_names[id]);
    int time = randomGaussian(9, 7);
    if (time < 0) time = 0;
    sleep(time);
    think_time[id] += time;
    printf("%s has thought for %d seconds\n", philosopher_names[id], think_time[id]);
}

// Philosopher routine executed in a separate thread
void *philosopher_routine(void *arg) {
    struct PhilosopherArgs *args = (struct PhilosopherArgs *)arg;

    while (think_time[args->id] < 100) {

        // Wait for chopsticks to be available
        wait_for_chopsticks(args->id);

        // Acquire chopsticks to start eating
        take_chopsticks(args->id);

        // Eat for a random time
        eat(args->id);

        // Put away chopsticks after eating
        put_away_chopsticks(args->id);

        // Think for a random time
        think(args->id);
    }

    // Print farewell message when leaving the table
    printf("%s is leaving the table. Bye!\n", philosopher_names[args->id]);

    // Return from the thread
    return NULL;
}


int main() {
    struct PhilosopherArgs args[NUM_PHILOSOPHERS];

    // Initialize mutexes for chopsticks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (pthread_mutex_init(&chopsticks[i], NULL) != 0) {
            printf("%d, Couldn't initialize mutex\n", errno);
            exit(1);
        }
    }

    // Create threads for each philosopher
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        args[i].id = i;
        pthread_create(&philosophers[i], NULL, philosopher_routine, (void *)&args[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes after use
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    return 0;
}
