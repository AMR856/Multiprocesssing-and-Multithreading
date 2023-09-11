#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

/**
 * First Pipe: The child writes to it (only writing to the child)
 * and the parent only reads from it 
 * Second Pipe: The parent write to it (only writing to the parent)
 * and the child only reads from it
 * 
 * Child -> Parent  (First Pipe)
 * Parent -> Child  (Second Pipe)
*/

int main(void)
{
    int myPip1[2];
    int myPip2[2];
    if (pipe(myPip1) == -1 || pipe(myPip2) == -1)
    {
        printf("Could create the pipes\n");
        exit(1);
    }
    int pid = fork();
    if (pid == -1)
    {
        printf("Couldn't fork\n");
        exit(2);
    }
    if (pid == 0)
    {
        /*Child process*/
        close(myPip1[0]);
        close(myPip2[1]);
        srand(time(NULL));
        int theSentNum = rand() % 20;
        if (write(myPip1[1], &theSentNum, sizeof(int)) == -1)
        {
            printf("Couldn't write\n");
            exit(3);
        }
        printf("Wrote the num %d child here\n", theSentNum);
        if (read(myPip2[0], &theSentNum, sizeof(int)) == -1)
        {
            printf("Couldn't read the num\n");
            exit(4);
        }
        printf("Read the num %d child here\n", theSentNum);
        printf("%d\n",theSentNum);
        close(myPip1[1]);
        close(myPip2[0]);
    }
    else
    {
        /*Parent process*/
        close(myPip1[1]);
        close(myPip2[0]);
        int therecievedNum;
        if (read(myPip1[0], &therecievedNum, sizeof(int)) == -1)
        {
            printf("Couldn't read\n");
            exit(5);
        }
        printf("Read the num %d parent here\n", therecievedNum);
        therecievedNum = therecievedNum * 4;
        if (write(myPip2[1], &therecievedNum, sizeof(int)) == -1)
        {
            printf("Couldn't write the num\n");
            exit(6);
        }
        printf("Wrote the num %d parent here\n", therecievedNum);
        close(myPip1[0]);
        close(myPip2[1]);
    }
}