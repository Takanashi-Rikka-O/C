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
		if (fork_result == (pid_t)-1)
		{
			perror("Fork failure..");
			exit(EXIT_FAILURE);
		}
		else;

		if (fork_result == (pid_t)0)
		{
			//	there is sub process


			close(0);	//	close stdin...
			dup(file_pipes[0]);	//	relink 0 to read...
			close(file_pipes[0]);	//	close the default read... file_pipes[0]
			close(file_pipes[1]);	//	close the default write... file_pipes[1]

			execlp("od","od","-c",(char*)0);	//	execlp can auto search for the executable_file's path

			exit(EXIT_FAILURE);


/*

			sprintf(buffer,"%d",file_pipes[0]);
			(void)execl("./pipe4","pipe4",buffer,(char*)0);
			exit(EXIT_FAILURE);

*/

		}
		else{
			//	there is father process

			close(file_pipes[0]);		//	close the fater's default read.... file_descriptor

			
			
	


			data_processed=write(file_pipes[1],some_data,strlen(some_data));
			close(file_pipes[1]);	//	close the father_process's default write .. file_descriptor
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
