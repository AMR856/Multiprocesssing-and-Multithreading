#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void){
    pid_t pid = fork();
    char *name = "Amr Alnas";
    if (pid < 0){
        printf("Error while forking\n");
        exit(1);
    }
    else if (pid == 0){
        printf("We're in the child process\n");
        printf("Parent id for the child: %d\n", getppid());
        printf("Child id: %d\n", getpid());
        printf("Username: %s\n", name);
    }
    else {
        name = "Amr Sorya";
        printf("We're in the parent process\n");
        printf("Parent id for the parent: %d\n", getppid());
        printf("Current id: %d\n", getpid());
        printf("Username: %s\n", name);
    }
}