#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
	pid_t pid;
	char* message;
	int n;
	int exit_code;


	printf("fork program starting\n");
	
	pid=fork();	//	copy current_process

	switch (pid)
	{
		case -1:
			perror("fork failed\n");
			exit(1);
		case 0:
			message="This is the child";
			n=3;
			exit_code=37;
			break;
		default:
			message="This is the parent";
			n=5;
			exit_code=0;
			break;
	}

	for (; n > 0; --n)
	{
		puts(message);
		sleep(1);
	}
	
	if (pid != 0)
	{
		int stat_val;		// definition in the sys/wait.h file..
		pid_t child_pid;	// child_process' PID
		
		child_pid=wait(&stat_val);	// if pid != 0 this process is parent_process
		printf("Child has finished: PID = %d\n",child_pid);		
		if (WIFEXITED(stat_val))
			printf("Child exited with code %d\n",WEXITSTATUS(stat_val));	
		else
			printf("Child terminated abnormally\n");
	}
	else
		printf("Current is child_process\n");



	exit(exit_code);
}
