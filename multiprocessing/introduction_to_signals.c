#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/wait.h>

typedef __pid_t pid_t;
void handle_signal(int);

int main(void) {
    pid_t pid = fork();
    if (pid == -1){
        printf("Something occured while creating the process\n");
        return 1;
    }
    if (pid == 0) {
        signal(SIGTERM, handle_signal);
        while (true) {
            printf("I'm still looping\n");
            usleep(50000);
        }
    } else {
        sleep(1);
        kill(pid, SIGTERM);
        wait(NULL);
    }
}

void handle_signal(int sig) {
    printf("I'm gonna finish looping now sorry\n");
    exit(0);
}
