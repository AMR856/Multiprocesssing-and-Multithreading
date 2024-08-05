#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define FIFO_MODE 0777

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Missing commands arguments\n");
        printf("You should provide the FIFO name and the data to be written to it\n");
        return 1;
    }
    if (mkfifo(argv[1], FIFO_MODE) == -1) {
        if (errno != EEXIST) {
            printf("Couldn't create the FIFO file\n");
            return 2;
        }
    }
    int file_descriptor = open(argv[1], O_WRONLY);
    if (file_descriptor == -1) {
        printf("Couldn't open the FIFO for writing\n");
        return 3;
    }
    int str_length = strlen(argv[2]);
    if (write(file_descriptor, argv[2], str_length) == -1) {
        printf("Couldn't write to the FIFO file\n");
        return 4;
    }
    close(file_descriptor);
    return EXIT_SUCCESS;
}
