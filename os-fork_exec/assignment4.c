#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if(pid == 0){
        execl("/bin/grep", "grep", "main", "test.txt", NULL);
        perror("execl");
    }else {
        wait(NULL);
        printf("Parent process completed\n");
    }
    return 0;
    
}