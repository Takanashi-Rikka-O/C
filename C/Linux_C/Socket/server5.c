#include<sys/types.h>			//	socket types
#include<sys/socket.h>			//	socket interface
#include<netinet/in.h>			//	AF_INET address
#include<unistd.h>			//	POSIX interface
//#include<signal.h>			//	SIGNAL interface
#include<stdio.h>		
#include<stdlib.h>
#include<sys/time.h>			//	interface - select
#include<sys/ioctl.h>			//	I/O control





int main()
{
	int server_sockfd,client_sockfd;	//	server and client' socket_descriptor
	int server_len,client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	//	server socket and client socket address
	

	int result;				//	return value
	fd_set readfds, testfds;		//	descriptors struct


	server_sockfd=socket(AF_INET,SOCK_STREAM,0);	//	AF_INET TCP/IP
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_address.sin_port=htons(9734);
	server_len=sizeof(server_address);
	//	server' address struct

	bind(server_sockfd,(struct sockaddr*)&server_address,server_len);	//	set port
	listen(server_sockfd,5);			//	set litsen queue with the server_sockfd


	FD_ZERO(&readfds);			//	initialize for the 'readfds'
	FD_SET(server_sockfd,&readfds);		//	Into the readfds with server_sockfd


//	(void)signal(SIGCHLD,SIG_IGN);			//	get signal-SIGCHLD and ignore

	while (1)
	{
		char ch;
		int fd;				//	descriptor	count
		int nread;			//	ioctl read bytes
	

		testfds=readfds;		//	struct = struct		testfds - server listen fd

		printf("server waiting..\n");

		result=select(FD_SETSIZE,&testfds,(fd_set*)0,(fd_set*)0,(struct timeval*)0);
		//	wait link with client.. and not timeout
		//	If have any descriptors already read in the testfds.. Link from client..

		if (result < 1)
		{
			perror("server5");
			exit(1);
		}
		else;

		for (fd=0; fd<FD_SETSIZE; ++fd)
		{
			if (FD_ISSET(fd,&testfds))	//	server_sockfd in testfds.. only
			{
				if (fd == server_sockfd)
				{	
					client_len=sizeof(client_address);
					client_sockfd=accept(server_sockfd,(struct sockaddr*)&client_address,&client_len);
					//	Link start
					FD_SET(client_sockfd,&readfds);		//	readfds link fd

					printf("adding client on fd %d \n",client_sockfd);
				}
				else
				{
					ioctl(fd,FIONREAD,&nread);	//	I/O read
					
					if (nread == 0)
					{
						close(fd);		//	OFF link from client
						FD_CLR(fd,&readfds);
						printf("removing client on fd %d\n",fd);	//	message
					}
					else		//	service
					{
						read(fd,&ch,1);
						sleep(5);
						printf("serving client on fd %d \n",fd);
						ch++;
						write(fd,&ch,1);
					}
				}
			}
			else;
		}
	}
//	exit(EXIT_SUCCESS);
}
