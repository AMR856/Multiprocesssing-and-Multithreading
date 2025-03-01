#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

typedef __pid_t pid_t;
int main(void) {
    pid_t pid1 = fork();
    pid_t pid2 = fork();
    if (pid1 == 0) {
        if (pid2 == 0) printf("We're in the child of the child and my parent id is %d and my id is %d\n", getppid(), getpid());
        else printf("We're in the child-1 of the parent and my parent id is %d and my id is %d\n", getppid(), getpid());
    } else {
        if (pid2 == 0) printf("We're in the child-2 of the parent my parent id is %d and my id is %d\n", getppid(), getpid());
        else printf("We're in the parent and my id is %d\n", getpid());
    }
    while (wait(NULL) != -1 || errno != ECHILD) printf("Waited for a child to terminate\n");
    return EXIT_SUCCESS;
}

// name                 pid1            pid2               
// ----------           ----------      ----------
// parent               x               y          
// parent-child-1       0               z 
// parent-child-2       x               0   
// child-child          0               0   
