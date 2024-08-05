#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ARRAY_SIZE 100

typedef __pid_t pid_t;
int main(int argc, char **argv) {
    int file_descriptors[2];
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
        close(file_descriptors[0]);
        char sent_array[ARRAY_SIZE];
        printf("Please, enter your name:\n");
        fgets(sent_array, ARRAY_SIZE, stdin);
        if (write(file_descriptors[1], sent_array, sizeof(sent_array)) == -1) {
            printf("Something occured while making the writing\n");
            return 3;
        }
        close(file_descriptors[1]);
    } else {
        close(file_descriptors[1]);
        char received_array[ARRAY_SIZE];
        if (read(file_descriptors[0], received_array, sizeof(received_array)) == -1){
            printf("Something occured while making the reading\n");
            return 4;
        }
        long int input_length = strlen(received_array);
        received_array[input_length - 1] = '\0';
        printf("Received this from my child: %s\nThank god he cares about me\n", received_array);
        close(file_descriptors[0]);
    }
    return EXIT_SUCCESS;
}

// file_descriptors 0 -> reading
// file_descriptors 1 -> writing
