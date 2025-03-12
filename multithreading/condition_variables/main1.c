#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t fuel_cond;
int fuel = 0;

void* fill_fuel(void *ptr){
    for (int i = 0; i < 5; i ++){
        pthread_mutex_lock(&mutex);
        fuel += 15;
        printf("Filling fuel, now it's: %d\n", fuel);
        pthread_mutex_unlock(&mutex);
        pthread_cond_broadcast(&fuel_cond);
        sleep(2);
    }

}   

void *car(void *ptr){
    pthread_mutex_lock(&mutex);
    while (fuel < 40) {
        printf("No fuel. Waiting...\n");
        pthread_cond_wait(&fuel_cond, &mutex);
        // Equivalent to:
        // pthread_mutex_unlock(&mutexFuel);
        // wait for signal on condFuel
        // pthread_mutex_lock(&mutexFuel);
    }
    fuel -= 40;
    printf("Got fuel. Now left: %d\n", fuel);
    pthread_mutex_unlock(&mutex);
}

int main(void){
    pthread_t threads[5];
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&fuel_cond, NULL);
    for (int i = 0; i < 5; i++){
        if (i == 3 || i == 4) {
            if (pthread_create(&threads[i], NULL, &fill_fuel, NULL)) exit(1);
        }
        else {
            if (pthread_create(&threads[i], NULL, &car, NULL)) exit(1);
        }
    }
    for (int i = 0; i < 5; i++) {
        if (pthread_join(threads[i], NULL))
            exit(1);
    }
    pthread_cond_destroy(&fuel_cond);
    pthread_mutex_destroy(&mutex);
}
