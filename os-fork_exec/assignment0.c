#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("Parent process (PID: %d)\n", getpid());

    if (fork() == 0) {
        printf("Child (PID: %d Parent PID: %d)\n", getpid(),getppid());
    }

    if (fork() == 0) {
        printf("Child (PID: %d Parent PID: %d)\n", getpid(),getppid());
    }

    if (fork() == 0) {
        printf("Child (PID: %d Parent PID: %d)\n", getpid(),getppid());
    }

    sleep (8);
    return 0;
}
