#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

//		Server code


int main()
{
	int server_sockfd,client_sockfd;	//	statement server_filedescriptor and client_filedescriptor
	int server_len,client_len;		//	server and client data long
	
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;
	//	server and client address
	
	unlink("server_socket");	//	rm server_socket file
	server_sockfd=socket(AF_UNIX,SOCK_STREAM,0);	//	create server' socket
	
	server_address.sun_family=AF_UNIX;
	strcpy(server_address.sun_path,"server_socket");	//	server socket' name
	server_len=sizeof(server_address);		//	long
	
	bind(server_sockfd,(struct sockaddr*)&server_address,server_len);	//	Give name of server socket
	
	listen(server_sockfd,5);	//	create server socket' queue	long is 5

	while (1)
	{
		char ch;
		printf("server waiting\n");
		
		client_len=sizeof(client_address);
		client_sockfd=accept(server_sockfd,(struct sockaddr*)&client_address,(socklen_t*)&client_len);
		//	Link with client	accpet() interface
		
		read(client_sockfd,&ch,1);	//	POSIX interface
		ch++;
		write(client_sockfd,&ch,1);	//	POSIX interface
		close(client_sockfd);		//	off client file_descriptor
	}

}
