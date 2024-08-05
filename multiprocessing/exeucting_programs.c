#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>
#include <errno.h>

extern char **environ;
#define URL "www.google.com"
#define PING_PATH "/usr/bin/ping"
#define COMMAND "ping"

int main(int argc, char **argv){
    char *arguments_array[] = {PING_PATH, URL, "-c", "3", NULL};
    char *arguments_array_with_path[] = {COMMAND, URL, "-c", "3", NULL};

    // execl(PING_PATH, PING_PATH, URL, "-c", "3", NULL);
    // execlp(COMMAND, COMMAND, URL, "-c", "3", NULL);
    // execle(PING_PATH, PING_PATH, URL, "-c", "3", NULL, environ);
    // execv(PING_PATH, arguments_array);
    // execve(PING_PATH, arguments_array, environ);
    execvp(COMMAND, arguments_array_with_path);
    printf("Command wasn't executed\nwith erorr: %d\n", errno); // 2 -> ENOENT if we write the command wrong
    return EXIT_SUCCESS;
}

/**
 * exec -> execute
 * execl -> List (We pass everything as arguments not array)
 * execle -> List with enviorment
 * execlp -> List also but with P means the PATH enviorment variable
 * 
 * execv -> Vector (We pass the argument as an array)
 * execve -> Vector and the enviroment for the program
 * execvp -> Vector with the PATH enviroment variable
 * 
 * all errors can be found in errno-base.h
*/
