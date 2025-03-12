#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>


void *some_routine(void *ptr){
    printf("We're wasting time here\n");
    sleep(2);
}

int main(void){
    pthread_t threads[10];
    for (int i = 0; i < 10; i++){
        if (pthread_create(&threads[i], NULL, some_routine, NULL)) exit(1);
    }
    pthread_exit(NULL);
    for (int i = 0; i < 10; i++){
        if (pthread_join(threads[i], NULL)) exit(1);
    }
    while(1) printf("Won't get here\n");;
    while(NULL) printf("Uselss print statment\n");
}