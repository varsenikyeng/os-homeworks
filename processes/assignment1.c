#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main ()
{
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    if (pid == 0)
    {
        printf("Child pid : %d \n" , getpid());
        exit(0);
    }
    else
    {
        printf("Parent pid : %d \n" , getpid());
    }
}
