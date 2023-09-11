#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>

int main(void)
{
    int arr[5];
    srand(time(NULL));
    for(int i = 0; i < 5; i++)
        arr[i] = rand() % 10;
    
    int fd = open("myFifo", O_RDWR);
    if (fd == -1)
    {
        printf("Couldn't open fifo\n");
        return (1);
    }
    if (write(fd, arr, sizeof(arr)) == -1)
    {
        printf("Couldn't write\n");
        return (2);
    }
    printf("Sent Numbers\n");
    int theRecievedNum;
    if (read(fd, &theRecievedNum, sizeof(theRecievedNum)) == -1)
    {
        printf("We couldn't recieve the number\n");
        return (3);
    }
    printf("We recieved the sum back hayyyyyyy\n");
    printf("Here it is %d\n", theRecievedNum);
    close(fd);
}
