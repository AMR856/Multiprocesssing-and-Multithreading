#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

void* printing_routine(void *ptr){
    while (true){
        int *thread_num = (int *) ptr;
        printf("Thread Num is: %d\n", *thread_num);
        sleep(2);
    }
}

int main(void){
    pthread_t thread1, thread2;
    int thread_num1 = 5, thread_num2  = 10;
    int *ptr1 = &thread_num1, *ptr2 = &thread_num2;
    if (pthread_create(&thread1, NULL, &printing_routine, (void *)ptr1)) exit(1);
    if (pthread_create(&thread2, NULL, &printing_routine, (void *)ptr2)) exit(1);
    if (pthread_join(thread1, NULL)) exit(1);
    if (pthread_join(thread2, NULL)) exit(1);
}