#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/wait.h>

typedef __pid_t pid_t;
void handle_signal(int sig);

int main(void) {
    pid_t pid = fork();
    if (pid == -1) {
        printf("Something occurred while creating the process\n");
        return 1;
    }
    if (pid == 0) {
        signal(SIGTERM, handle_signal);
        while (true) {
            printf("I'm still looping\n");
            usleep(50000);
        }
    } else {
        kill(pid, SIGSTOP);
        int t;
        do {
            printf("Time you want to run the process: ");
            scanf("%d", &t);

            if (t > 0) {
                kill(pid, SIGCONT);
                sleep(t);
                kill(pid, SIGSTOP);
            }
        } while (t > 0);
        kill(pid, SIGCONT);
        kill(pid, SIGTERM);
        wait(NULL);
    }
    return 0;
}

void handle_signal(int sig) {
    printf("I'm gonna finish looping now, sorry\n");
    printf("You killed me by yourself\n");
    exit(0);
}
