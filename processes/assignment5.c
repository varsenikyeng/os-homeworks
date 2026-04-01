#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {
        printf("Child PID %d \n", getpid());
	sleep(10);
        exit(0);
    } else {
	wait(NULL);
        printf("Parent PID %d, child PID = %d\n  ...sleep... \n" ,getpid(), pid);
        sleep(20);
        printf("Parent done\n");
    }
}
