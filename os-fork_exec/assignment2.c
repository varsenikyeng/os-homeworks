#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1 = fork();
    if (pid1 == 0) {
        execl("/bin/ls", "ls", NULL);
        perror("execl");
        return 1;
    }
    //as the date was being run first
    wait(NULL);

    pid_t pid2 = fork();
    if (pid2 == 0) {
        execl("/bin/date", "date", NULL);
        perror("execl");
        return 1;
    }

    while (wait(NULL) > 0);

    printf("Parent process done\n");
    return 0;
}