#include"client.h"
#include<ctype.h>

int main()
{
	int server_fifo_fd,client_fifo_fd;	//	server and client  fifo_filedescriptors
	struct data_to_pass_st my_data;		//	data lock Object
	int times_to_send;			//	times
	char client_fifo[256];			//	buffer
	

	server_fifo_fd=open(SERVER_FIFO_NAME,O_WRONLY);		//	open server' fifo to wrtie
	if (server_fifo_fd == -1)		//	if true , open is failed
	{
		fprintf(stderr,"Sorry, no server\n");
		exit(EXIT_FAILURE);
	}
	else;

	my_data.client_pid=getpid();		//	write current_pid to struct member
	sprintf(client_fifo,CLIENT_FIFO_NAME,my_data.client_pid);	//	write string_information to buffer
	if (mkfifo(client_fifo,0777) == -1)	//	if true , mkfifo is failed.. 
	{
		fprintf(stderr,"Sorry, can't make %s\n",client_fifo);
		exit(EXIT_FAILURE);
	}
	else;

	for (times_to_send=0; times_to_send<5; ++times_to_send)		//	Number of tasks ...is 5
	{
		sprintf(my_data.some_data,"Hello from %d",my_data.client_pid);	//	data
		printf("%d sent %s, ",my_data.client_pid,my_data.some_data);	//	message
		write(server_fifo_fd,&my_data,sizeof(my_data));		//	write data block to server' fifo
		client_fifo_fd=open(client_fifo,O_RDONLY);		//	open client' fifo

		if (client_fifo_fd != -1)		//	if true success
		{
			if (read(client_fifo_fd,&my_data,sizeof(my_data)) > 0)		//	if true have datas
			{
				printf("received: %s\n",my_data.some_data);		//	some_data is changed to capital
			}
			else;
			close(client_fifo_fd);		//	off client' fifo
		}
		else
			perror("Open client' fifo is failed");
	}

	close(server_fifo_fd);		//	off server' fifo
	unlink(client_fifo);		//	delete client' fifo_file

	exit(EXIT_SUCCESS);
}
