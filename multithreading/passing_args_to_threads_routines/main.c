#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 27};
void *sum_prime(void *ptr){
    int *index = (int *)ptr;
    int *sum = (int *)malloc(sizeof(int));
    for (int i = 0; i < 5; i++){
        *sum += primes[i + *index];
    } 
    free(ptr);
    printf("Local sum is: %d\n", *sum);
    return (void *)sum;
}

// void *print_prime(void *ptr){
//     int *index = (int *)ptr;
//     printf("%d\n", primes[*index]);
//     free(ptr);
// }

int main(void){
    pthread_t threads[2];
    int *a;
    for (int i = 0; i < 2; i++){
        a = (int *)malloc(sizeof(int));
        *a = i * 5;
        if (pthread_create(&threads[i], NULL, &sum_prime, a)) exit(1);
    }
    int sum = 0;
    int *temp_sum;
    for (int i = 0; i < 2; i++){
        pthread_join(threads[i], (void **) &temp_sum);
        sum += *temp_sum;
        free(temp_sum);
    }
    printf("%d\n", sum);
}

// int main(void){
//     pthread_t threads[10];
//     for (int i = 0; i < 10; i++) {
//         int *a = (int *)malloc(sizeof(int));
//         *a = i;
//         if (pthread_create(&threads[i], NULL, print_prime, a)) exit(1);
//     }
//     for (int i = 0; i < 10; i++){
//         if (pthread_join(threads[i], NULL)) exit(1);
//     }
// }
