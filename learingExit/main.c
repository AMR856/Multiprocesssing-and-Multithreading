#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main(void)
{
    int id = fork();
    if (id == -1)
    {
        printf("Couldn't fork\n");
        return (1);
    }

    if (id == 0)
    {
        int myError = execlp("ping", "ping", "-c", "1", "google.con", NULL);
        if (myError == -1)
        {
            printf("Couldn't execute the command\n");
            exit(2);
        }
    }
    else
    {
        int wstatus;
        wait(&wstatus);
        if (WIFEXITED(wstatus))
        {
            int codestatus = WEXITSTATUS(wstatus);
            if (codestatus == 0)
                printf("Success\n");
            else
                printf("Failed\n");
        }
    }
    return (0);
}