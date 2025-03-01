#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

typedef __pid_t pid_t;
int main(void) {
    int process_id = getpid();
    pid_t pid = fork();
    int n;
    if (pid == 0) n = 1;
    else n = 6;
    if (getpid() == process_id) wait(NULL); // -> I can get the id of the process I waited for
    int i;
    for (i = n; i < n + 5; i++){
        printf("%d ", i);
        fflush(stdout);
    }
    if (process_id == getpid()) printf("\n");
    if (getppid() == process_id) exit(0);
    printf("Only the parent will get here\n");
    return EXIT_SUCCESS;
}
