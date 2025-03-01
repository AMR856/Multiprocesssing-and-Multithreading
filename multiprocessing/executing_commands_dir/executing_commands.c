#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define URL "www.google.com"
#define PING_PATH "/usr/bin/ping"
#define FILE_MODE 0777
extern char **environ;

typedef __pid_t pid_t;
int main(int argc, char **argv){
    if (argc != 2) {
        printf("Missing commands arguments\n");
        printf("You should provide the name of new output file\n");
        return 1;
    }
    pid_t pid = fork();
    if (pid == -1){
        printf("Something occured while creating the process\n");
        return 2;
    }
    if (pid == 0) {
        int file_descriptor = open(argv[1], O_WRONLY | O_CREAT, FILE_MODE);
        if (file_descriptor == -1) {
            printf("Couldn't write or create the file\n");
            return 3;
        }
        int file_descriptor_2 = dup2(file_descriptor, STDOUT_FILENO);
        close(file_descriptor);
        int err = execle(PING_PATH, PING_PATH, URL, "-c", "3", NULL, environ);
        if (err == -1) {
            printf("Couldn't find the program to execute\n");
            return 4;
        }
    } else {
        int wait_status;
        wait(&wait_status);
        if (WIFEXITED(wait_status)) {
            int status_code = WEXITSTATUS(wait_status);
            if (!status_code) printf("Success\n");
            else printf("Failure\n");
        }
    }
    return EXIT_SUCCESS;
}
