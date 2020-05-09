#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<limits.h>
#include<sys/types.h>
#include<sys/stat.h>

#define SERVER_FIFO_NAME "./server_fifo"		//	the server use fifo
#define CLIENT_FIFO_NAME "./client_%d_fifo"		//	the client use fifo

#define BUFFER_SIZE 20					//	array size

struct data_to_pass_st					// 	data block
{
	pid_t client_pid;
	char some_data[BUFFER_SIZE+1];
};
