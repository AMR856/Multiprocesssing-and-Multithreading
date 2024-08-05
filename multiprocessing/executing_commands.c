#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>

#define URL "www.google.com"
#define PING_PATH "/usr/bin/ping"

extern char **environ;

typedef __pid_t pid_t;
int main(int argc, char **argv){
    pid_t pid = fork();
    if (pid == -1){
        printf("Something occured while creating the process\n");
        return 1;
    }
    if (pid == 0) {
        execle(PING_PATH, PING_PATH, URL, "-c", "3", NULL, environ);
    } else {
        wait(NULL);
        printf("Success\n");
    }
    return EXIT_SUCCESS;
}
