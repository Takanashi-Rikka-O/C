#include<sys/types.h>
#include<sys/time.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/ioctl.h>

int main()
{
	char buffer[128];
	int result,nread;
	
	fd_set inputs,testfds;		//	struct for descriptors
	struct timeval timeout;		//	select' parameter.. timeout..
	
	FD_ZERO(&inputs);		//	initialize 
	FD_SET(0,&inputs);		//	linux 0 - read 1 - write 2 - error
	

	while (1)
	{	
		testfds=inputs;		//	struct = strcut
		timeout.tv_sec=2;	//	seconds
		timeout.tv_usec=500000;	//	microseconds

		result=select(FD_SETSIZE,&testfds,(fd_set*)NULL,(fd_set*)NULL,&timeout);
			//	max_test  read		write	error		timeout

		switch (result)
		{
			case 0:
				printf("Timeout\n");
				break;
			case -1:
				perror("select failed");
				exit(1);
			default:
				if (FD_ISSET(0,&testfds))
				{
					ioctl(0,FIONREAD,&nread);
					if (nread == 0)
					{
						printf("keyboard done\n");
						exit(0);
					}
					else;
					
					nread=read(0,buffer,nread);
					buffer[nread]='\0';
					printf("read %d from keyboard : %s",nread,buffer);
				}
				else;
				break;
		}
	}


	exit(EXIT_SUCCESS);
}
