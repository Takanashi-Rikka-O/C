#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(void)
{
	int data_processed;
	int file_pipes[2];
	const char some_data[]="123";
	char buffer[BUFSIZ+1];
	pid_t fork_result;

	memset(buffer,'\0',sizeof(buffer));

	if (pipe(file_pipes) == 0)
	{
		fork_result=fork();	//	fork_result is PID
		if (fork_result == -1)
		{
			perror("Fork failure..");
			exit(EXIT_FAILURE);
		}
		else;

		if (fork_result == 0)
		{
			sprintf(buffer,"%d",file_pipes[0]);
			(void)execl("./pipe4","pipe4",buffer,(char*)0);
			exit(EXIT_FAILURE);
		}
		else{
			data_processed=write(file_pipes[1],some_data,strlen(some_data));
			printf("%d -- Wrote %d bytes\n",getpid(),data_processed);
			pid_t re;
			re=wait(NULL);
			printf("Process %d is over..\n",re);
		}
	}
	else
	{
		perror("pipe failed..");
		exit(5);
	}

	//wait(&fork_result);



	exit(EXIT_SUCCESS);
}
