#include"client.h"
#include<ctype.h>

int main()
{
	int server_fifo_fd,client_fifo_fd;		//	server and client fifo_file
	struct data_to_pass_st my_data;			//	data block
	int read_res;					//	server use read return quantity

	char client_fifo[256];				//	client_fifo sent data buffer
	char* tmp_char_ptr;				//	temp char PTR


	mkfifo(SERVER_FIFO_NAME,0777);			//	create server's fifo_file
	server_fifo_fd=open(SERVER_FIFO_NAME,O_RDONLY);	//	open server's fifo_file

	if (server_fifo_fd == -1)			//	if is true open is failed
	{
		fprintf(stderr,"Server fifo failure\n");
		exit(EXIT_FAILURE);
	}
	else;						//	otherwise is open success

	sleep(10);

	do
	{
		read_res=read(server_fifo_fd,&my_data,sizeof(my_data));	//	read a data block from fifo
		if (read_res > 0)	//	if > 0 readed data block
		{
			tmp_char_ptr=my_data.some_data;		//	some_data is the struct member...
			while (*tmp_char_ptr)
			{
				*tmp_char_ptr=toupper(*tmp_char_ptr);	//	change data to capital
				tmp_char_ptr++;
			}
			sprintf(client_fifo,CLIENT_FIFO_NAME,my_data.client_pid);	//	write to buffer
			
			client_fifo_fd=open(client_fifo,O_WRONLY);	//	client_fifo is client-fifo's path
			
			if (client_fifo_fd != -1)			//	not is -1 , open success
			{	
				write(client_fifo_fd,&my_data,sizeof(my_data));		//	write a struct data block
				close(client_fifo_fd);		//	off client's fifo_file
			}
			else;
		}
		else	perror("Not have data\n");
	} while(read_res>0);

	close(server_fifo_fd);		//	off server's fifo
	unlink(SERVER_FIFO_NAME);	//	delete server's fifo_file
	exit(EXIT_SUCCESS);		//	exit
}
