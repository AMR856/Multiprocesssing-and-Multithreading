#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int mails = 0;

void *mails_routine(void *ptr){
    for (int i = 0; i < 1000000; i++) mails++;
}

int main(void){
    pthread_t thread1, thread2;
    if (pthread_create(&thread1, NULL, &mails_routine, NULL)) exit(1);
    if (pthread_create(&thread2, NULL, &mails_routine, NULL)) exit(1);
    if (pthread_join(thread1, NULL)) exit(1);
    if (pthread_join(thread2, NULL)) exit(1);
    printf("Mails: %d\n", mails);
}
