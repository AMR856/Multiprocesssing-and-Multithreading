#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

void *roll_dice(void *ptr){
    int *x = malloc(sizeof(int));
    *x = (rand() % 6) + 1;
    printf("Address of x: %p in the function\n", x);
    return (void *) x;
}


int main(void){
    srand(time(NULL));
    int *x[7];
    pthread_t th[7];
    for (int i = 0; i < 7; i++){
        if (pthread_create(&th[i], NULL, &roll_dice, NULL))
            exit(1);
    }
    for (int i = 0; i < 7; i++){
        if (pthread_join(th[i], (void **) &x[i]))
            exit(1);
    }
    for (int i = 0; i < 7; i++){
        printf("Value of x: %d in the %ith iteration\n", *x[i], i);
        printf("Address of x is: %p\n", x[i]);
        free(x[i]);
    }
}
