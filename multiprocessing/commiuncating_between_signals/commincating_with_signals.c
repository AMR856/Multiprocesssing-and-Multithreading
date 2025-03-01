#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX_ARRAY_SIZE 100

char name_array[MAX_ARRAY_SIZE] = {'\0'};
void sigusr1_handler(int);
typedef __pid_t pid_t;
int main(void) {
    pid_t pid = fork();
    if (pid == -1){
        printf("Something occured while creating the process\n");
        return 2;
    }
    if (pid == 0) {
        sleep(5);
        kill(getppid(), SIGUSR1);
    } else {
        struct sigaction sa;
        sa.sa_handler = &sigusr1_handler;
        sa.sa_flags = SA_RESTART;
        sigaction(SIGUSR1, &sa, NULL);
        printf("What is your name: \n");
        fgets(name_array, MAX_ARRAY_SIZE, stdin);
        name_array[strlen(name_array) - 1] = '\0';
        printf("Thank you, %s\n", name_array);
        wait(NULL);
    }
    return EXIT_SUCCESS;
}

void sigusr1_handler(int) {
    if (!name_array[0])
        printf("Please, enter your name, what are you waiting for\n");
}
