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
        printf("You should provide the number of numbers you want to generate\n");
        return 1;
    }
    if (mkfifo("generating_fifo", FIFO_MODE) == -1) {
        if (errno != EEXIST) {
            printf("Couldn't create the FIFO file\n");
            return 2;
        }
    }
    int array_size = atoi(argv[1]);
    int generating_array[array_size];
    srand(time(NULL));
    for (int i = 0; i < array_size; i++) {
        generating_array[i] = rand() % 50;
        printf("Generated: %d\n", generating_array[i]);
    }
    int file_descriptor = open("generating_fifo", O_WRONLY);
    if (file_descriptor == -1) {
        printf("Couldn't open the FIFO for writing\n");
        return 3;
    }
    if (write(file_descriptor, generating_array, sizeof(int) * array_size) == -1) {
        printf("Couldn't write to the FIFO file\n");
        return 4;
    }
    close(file_descriptor);
    file_descriptor = open("generating_fifo", O_RDONLY);
    if (file_descriptor == -1) {
        printf("Couldn't open the FIFO for reading\n");
        return 5;
    }
    int sum;
    if (read(file_descriptor, &sum, sizeof(int)) == -1) {
        printf("Couldn't read from the FIFO file\n");
        return 6;
    }
    close(file_descriptor);
    printf("The total sum is: %d\n", sum);
    return EXIT_SUCCESS;
}

// gcc generator.c -o main1
