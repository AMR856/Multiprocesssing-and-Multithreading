#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "practical_use_fork.h"

typedef __pid_t pid_t;
int main(int argc, char **argv) {
    int file_descriptors[2];
    int array_size = sizeof(arr) / sizeof(int);
    int start, end;
    if (pipe(file_descriptors) == -1) {
        printf("Something occured while making the pipe\n");
        return 1;
    }
    pid_t pid = fork();
    if (pid == -1) {
        printf("Something occured while forking\n");
        return 2;
    }
    if (pid == 0) {
        start = 0;
        end = array_size / 2;
    } else {
        start = array_size / 2;
        end = array_size;
    }
    int sum = 0;
    for (int i = start; i < end; i++) {
        sum += arr[i];
    }
    if (pid == 0) {
        close(file_descriptors[0]);
        write(file_descriptors[1], &sum, sizeof(int));
        close(file_descriptors[1]);
    } else {
        int child_sum, total_sum;
        close(file_descriptors[1]);
        read(file_descriptors[0], &child_sum, sizeof(int));
        close(file_descriptors[0]);
        total_sum = sum + child_sum;
        printf("Total sum is: %d\n", total_sum);
    }
    return EXIT_SUCCESS;
}

// file_descriptors 0 -> reading
// file_descriptors 1 -> writing
// gcc practical_use_fork.h practical_use_fork.c -o main
