#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main ()
{
    pid_t pid1 = fork();
    int status1, status2;
    if (pid1 < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid1 == 0)
    {
        printf("Child pid : %d \n" , getpid());
        exit(3);
    }
    else
    {
        wait(&status1);
        printf("Parent pid : %d \n" , getpid());
    }
    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("fork failed");
        return 1;
    }

    if(pid2 == 0)
    {
        printf("Child pid : %d \n" , getpid());
        exit(4);
    }
    else
    {
        waitpid(pid2, &status2, 0);
        printf("Parent pid : %d \n" , getpid());
    }
    printf("child1 status :%d \n" , status1);
    printf("child2 status :%d \n" , status2);


}
