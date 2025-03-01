#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

char *name = "Amr Sorya";
void *thread1_routine(void *ptr){
    sleep(2);
    printf("%s\n", name);
}

void *thread2_routine(void *ptr){
    sleep(2);
    name = "Amr Sorya came back again";
    printf("%s\n", name);
}

int main(void){
    pthread_t thread1, thread2;
    if(pthread_create(&thread1, NULL, &thread1_routine, NULL)) exit(1);
    if(pthread_create(&thread2, NULL, &thread2_routine, NULL)) exit(1);
    if (pthread_join(thread1, NULL)) exit(1);
    if (pthread_join(thread2, NULL)) exit(1);
}
