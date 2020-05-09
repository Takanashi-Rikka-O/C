#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
	int data_processed;
	int file_pipes[2];
	const char some_data[]="123";
	char buffer[BUFSIZ+1];
	pid_t kksk;


	memset(buffer,'\0',sizeof(buffer));

	if (pipe(file_pipes) == 0)
	{
		kksk=fork();

		if (kksk == -1)
		{
			perror("fork failed..");
			exit(3);
		}
		else if (kksk != 0)
		{
			close(file_pipes[1]);	//	close write
			sleep(2);
			data_processed=read(file_pipes[0],buffer,BUFSIZ);	//	read

//			data_processed=write(file_pipes[1],some_data,strlen(some_data));
			printf("Readed %d bytes\n",data_processed);
			printf("Read -- %s\n",buffer);
			printf("PID : %d..F\n",getpid());
			//data_processed=read(file_pipes[0],buffer,BUFSIZ);
			//printf("Read %d bytes: %s\n",data_processed,buffer);
			(void)wait(NULL);
			printf("Write--process over\n");
		}
		else
		{
			close(file_pipes[0]);
			data_processed=write(file_pipes[1],some_data,strlen(some_data));
			printf("PID : %d..S - write over..  had %d \n",getpid(),data_processed);
			exit(3);
		}
	}
	else
	{
		perror("pipe interface failed...");
		exit(EXIT_FAILURE);
	}



	exit(EXIT_SUCCESS);
}
