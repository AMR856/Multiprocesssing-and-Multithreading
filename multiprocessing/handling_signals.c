#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/wait.h>

void sigtstp_handler(int);
void sigcont_handler(int sig);
int main(void){
    struct sigaction sa, sc;
    sa.sa_handler = &sigtstp_handler;
    sc.sa_handler = &sigcont_handler;
    sc.sa_flags = SA_RESTART;
    sa.sa_flags = SA_RESTART;
    // sigaction(SIGTSTP, &sa, NULL);
    sigaction(SIGCONT, &sc, NULL);
    int x;
    printf("Please, enter a number: ");
    scanf("%d", &x);
    printf("The result of %d * 5: %d\n", x, x * 5);
    return EXIT_SUCCESS;
}

void sigtstp_handler(int sig){
    printf("Stopping is not allowed\n");
}

void sigcont_handler(int sig){
    printf("Please, enter a number: ");
    fflush(stdout);
}
