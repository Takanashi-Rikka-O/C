#include<sys/types.h>			//	socket types
#include<sys/socket.h>			//	socket interface
#include<netinet/in.h>			//	AF_INET address
#include<unistd.h>			//	POSIX interface
#include<signal.h>			//	SIGNAL interface
#include<stdio.h>		
#include<stdlib.h>

int main()
{
	int server_sockfd,client_sockfd;	//	server and client' socket_descriptor
	int server_len,client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	//	server socket and client socket address
	
	server_sockfd=socket(AF_INET,SOCK_STREAM,0);	//	AF_INET TCP/IP
	
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_address.sin_port=htons(9734);
	server_len=sizeof(server_address);
	//	server' address struct

	bind(server_sockfd,(struct sockaddr*)&server_address,server_len);	//	set port
	listen(server_sockfd,5);			//	set litsen queue with the server_sockfd

	(void)signal(SIGCHLD,SIG_IGN);			//	get signal-SIGCHLD and ignore

	while (1)
	{
		char ch;
		printf("server waiting..\n");
		client_len=sizeof(client_address);
		client_sockfd=accept(server_sockfd,(struct sockaddr*)&client_address,&client_len);	//	wait link
		
		if (fork() == 0)	// if in child
		{
			read(client_sockfd,&ch,1);
			sleep(5);
			ch++;
			write(client_sockfd,&ch,1);
			close(client_sockfd);		//	off link of client
			exit(0);
		}
		else
			close(client_sockfd);

	}

	exit(EXIT_SUCCESS);
}
