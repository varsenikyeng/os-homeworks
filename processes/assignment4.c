#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
	pid_t pid1;
	pid_t pid2 ;
	int status;
	pid1 = fork();
	if(pid1 < 0)
	{
		perror("fork failed");
		exit(1);
	}
	if(pid1 == 0)
	{
		printf("Child1 pid : %d \n", getpid());
		exit(2);
	}
	pid2 = fork();
	if(pid2 < 0)
	{
		perror("fork failed");
		exit(1);
	}
	if(pid2 == 0)
	{
		printf("Child2 pid : %d \n", getpid());
		exit(9);
	}

	if (waitpid(pid1, &status, 0) > 0){
		if(WIFEXITED(status))
		{
			printf("Child 1 exited normally with code %d \n", WEXITSTATUS(status));
		}
		else
		{
			printf("CHild1 did not exit normally");
		}

	}
	if(waitpid(pid2, &status, 0) > 0){
		if(WIFEXITED(status))
		{
			printf("Child 2 exited normally with code %d \n", WEXITSTATUS(status));
		}
		else{
			printf("CHild2 did not exit normally");
		}
	}
}