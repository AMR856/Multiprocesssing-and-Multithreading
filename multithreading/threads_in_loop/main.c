#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int mails = 0;
pthread_mutex_t mutex;

void *mails_routine(void *ptr){
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    } 
}

int main(void){
    pthread_t th[1000];
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < 1000; i++){
        if (pthread_create(&th[i], NULL, &mails_routine, NULL)) exit(1);
        printf("Thread %d started execution\n", i);
    }
    for (int i = 0; i < 1000; i++){
        if (pthread_join(th[i], NULL)) exit(1);
        printf("Thread %d finished execution\n", i);
    }
    printf("Mails num is: %d\n", mails);
}
