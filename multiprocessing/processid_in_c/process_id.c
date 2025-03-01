#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

typedef __pid_t pid_t;
int main(void) {
    pid_t pid = fork();
    if (pid == 0) sleep(1);
    printf("Current Process ID: %d - Parent Process ID: %d\n", getpid(), getppid());
    int res = wait(NULL);
    if (res == -1) printf("I'm the child I don't wait for anything\n");
    else printf("I'm the parent and I waited for: %d and it's my child\n", res);
    return EXIT_SUCCESS;
}