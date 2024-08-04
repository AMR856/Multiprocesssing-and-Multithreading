#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef __pid_t pid_t;
int main(void) {
    pid_t pid = fork();
    if (pid == 0){
        printf("Hello from child process\n");
        exit(0);
    }
    printf("This the id of the parent: %d\n", (int)getpid());
    printf("The child won't get here\n");
    return EXIT_SUCCESS;
}
// fork();
// fork();
// fork();
// fork();
// 2 ^ 4
// flushing the output -> internal buffer -> cannot print very quickly
