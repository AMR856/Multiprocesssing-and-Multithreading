#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

pthread_mutex_t mutexes[4];
int fuels[4] = {100, 100, 100, 100};

void *consume_fuel(void *ptr){
    while (1) {
        for (int i = 0; i < 4; i++) {
            if (pthread_mutex_trylock(&mutexes[i]) == 0) { 
                int fuelNeeded = (rand() % 60) + 1;
                if (fuels[i] >= fuelNeeded) {
                    fuels[i] -= fuelNeeded;
                    printf("Using stove %d: Consumed %d fuel, left: %d\n", i, fuelNeeded, fuels[i]);
                    usleep(500000);
                } else {
                    printf("Stove %d has only %d fuel, skipping...\n", i, fuels[i]);
                    pthread_mutex_unlock(&mutexes[i]);
                    continue;
                }
                pthread_mutex_unlock(&mutexes[i]);
                return NULL;
            }
        }
        printf("No stove available, retrying...\n");
        usleep(300000);
    }
}

int main(void){
    pthread_t threads[10];
    for (int i = 0; i < 4; i++) pthread_mutex_init(&mutexes[i], NULL);
    for (int i = 0; i < 10; i++) {
        if (pthread_create(&threads[i], NULL, consume_fuel, NULL)) exit(1);
    }
    for (int i = 0; i < 10; i++) {
        if (pthread_join(threads[i], NULL)) exit(1);
    }
    for (int i = 0; i < 4; i++) pthread_mutex_destroy(&mutexes[i]);
    return 0;
}
