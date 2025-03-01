#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int mails = 0;
pthread_mutex_t mutex;

void *mails_routine(void *ptr){
    for (int i = 0; i < 1000000; i++){
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    } 
}

int main(void) {
    pthread_t thread1, thread2, thread3, thread4;
    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&thread1, NULL, &mails_routine, NULL)) exit(1);
    if (pthread_create(&thread2, NULL, &mails_routine, NULL)) exit(1);
    if (pthread_create(&thread3, NULL, &mails_routine, NULL)) exit(1);
    if (pthread_create(&thread4, NULL, &mails_routine, NULL)) exit(1);
    if (pthread_join(thread1, NULL)) exit(1);
    if (pthread_join(thread2, NULL)) exit(1);
    if (pthread_join(thread3, NULL)) exit(1);
    if (pthread_join(thread4, NULL)) exit(1);
    printf("Mails: %d\n", mails);
}
