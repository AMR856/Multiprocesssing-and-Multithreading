#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
// #include <error.h>
#include <stdlib.h>

pthread_mutex_t mutex;

void* trylock_play(void *){
    if (pthread_mutex_trylock(&mutex) == 0){
        printf("Got the luck by asking\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
    } else
        printf("Didn't get the lock\n");
}

void* normal_lock(void *){
    pthread_mutex_lock(&mutex);
    printf("Got the luck by force\n");
    sleep(1);
    pthread_mutex_unlock(&mutex);

}

int main(void){
    pthread_t threads[4];
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < 4; i++)
        if (pthread_create(&threads[i], NULL, trylock_play, NULL)) exit(1);
    for (int i = 0; i < 4; i++)
        if (pthread_join(threads[i], NULL)) exit(1);
    pthread_mutex_destroy(&mutex);
}
