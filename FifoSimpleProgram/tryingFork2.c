#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>


int main(void)
{
    int arr[5];
    int sum = 0;
    int fd = open("myFifo", O_RDWR);
    if (fd == -1)
    {
        printf("Couldn't open fifo\n");
        return (1);
    }
    if (read(fd, arr,  sizeof(arr)) == -1)
    {
        printf("Could write\n");
        return (2);
    }
    printf("Recieved Numbers\n");
    for(int i = 0; i < 5; i++)
    {
        sum = sum + arr[i];
    }
    printf("Here's the sum: ");
    printf("%d\n", sum);
    if (write(fd, &sum, sizeof(int)) == -1)
    {
        printf("We couldn't send the number\n");
        return (3);
    }
    printf("We sent the sum back hayyyyyyy\n");
    close(fd);
}