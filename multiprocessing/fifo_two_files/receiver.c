#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

#define FIFO_MODE 0777

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Missing commands arguments\n");
        printf("You should provide the number of numbers that were generated\n");
        return 1;
    }
    int array_size = atoi(argv[1]);
    int receiver_array[array_size];
    int sum = 0;
    int file_descriptor = open("generating_fifo", O_RDONLY);
    if (file_descriptor == -1) {
        printf("Couldn't open the FIFO for reading\n");
        return 3;
    }
    if (read(file_descriptor, receiver_array, sizeof(int) * array_size) == -1) {
        printf("Couldn't read from the FIFO file\n");
        return 4;
    }
    for (int i = 0; i < array_size; i++) sum += receiver_array[i];
    close(file_descriptor);
    file_descriptor = open("generating_fifo", O_WRONLY);
    if (file_descriptor == -1) {
        printf("Couldn't open the FIFO for writing\n");
        return 5;
    }
    if (write(file_descriptor, &sum, sizeof(int)) == -1) {
        printf("Couldn't write to the FIFO file\n");
        return 6;
    }
    close(file_descriptor);
    return EXIT_SUCCESS;
}

// gcc receiver.c -o main1
