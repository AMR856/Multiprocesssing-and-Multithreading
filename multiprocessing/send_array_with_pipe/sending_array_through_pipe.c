#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <sys/wait.h>

#define MAX_ARRAY_SIZE 100
// #define MAX_NUMBER_RANGE 11
typedef __pid_t pid_t;
int main(void){
    int file_descriptor[2];
    if (pipe(file_descriptor) == -1){
        printf("Couldn't create the pipe\n");
        return 1;
    }
    pid_t pid = fork();
    if (pid == -1){
        printf("Something occured while creating the process\n");
        return 2;
    }
    if (pid == 0) {
        close(file_descriptor[0]);
        int n, range;
        int sent_array[MAX_ARRAY_SIZE];
        srand(time(NULL));
        // n = rand() % 100 + 1;
        printf("Enter the number of random numbers you want to generate, and thier range: \n");
        scanf("%d %d", &n, &range);
        printf("Will generate %d random numbers\n", n);
        printf("Generating: ");
        for (int i = 0; i < n; i++) {
            sent_array[i] = rand() % range;
            printf("%d ", sent_array[i]);
        }
        printf("\n");
        if (write(file_descriptor[1], &n, sizeof(int)) == -1) {
            printf("Couldn't write to the parent pipe\n");
            return 4;
        }
        printf("Sent the size of the array\n");
        if (write(file_descriptor[1], sent_array, sizeof(int) * n) == -1) {
            printf("Couldn't write to the parent pipe\n");
            return 5;
        }
        printf("Sent the array\n");
        close(file_descriptor[1]);
    } else {
        int n, sum = 0;
        close(file_descriptor[1]);
        int recieved_array[MAX_ARRAY_SIZE];
        if (read(file_descriptor[0], &n, sizeof(int)) == -1) {
            printf("Couldn't read from the child pipe\n");
            return 4;
        }
        printf("Recieved the size of the array\n");
        if (read(file_descriptor[0], recieved_array, sizeof(int) * n) == -1) {
            printf("Couldn't read from the child pipe\n");
            return 4;
        }
        printf("Recieved the array\n");
        for (int i = 0; i < n; i++) sum += recieved_array[i];
        printf("Sum result is: %d\n", sum);
        close(file_descriptor[0]);
        wait(NULL);
    }
    return EXIT_SUCCESS;
}
// file_descriptors 0 -> reading
// file_descriptors 1 -> writing
