#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child
        //printf("Before exec\n");
        execl("/bin/ls", "ls", NULL);
        perror("execl");
    } else {
        wait(NULL);
        printf("Parent process done\n");
    }

    return 0;
}
