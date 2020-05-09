#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


//#include<sys/un.h>
//	Socket'head_file

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


int main()
{
	int sockfd;	//	Socket' file descriptor
	int len;
	//struct sockaddr_un address;	//	Socket' address
	struct sockaddr_in address;	

	int result;
	char ch='A';
	
	//	Create Socket..
	//sockfd=socket(AF_UNIX,SOCK_STREAM,0);
	
	sockfd=socket(AF_INET,SOCK_STREAM,0);	//	internet link
	
/*

	address.sun_family=AF_UNIX;		//	struct sockaddr_un' member
	strcpy(address.sun_path,"server_socket");	//	Socket' name

*/

	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");		//	localhost
	//	inet_addr can change IP with text string
	address.sin_port=9734;


	len=sizeof(address);		//	Socket long
	
	result=connect(sockfd,(struct sockaddr*)&address,len);		//	connect to server

	if (result == -1)
	{
		perror("oops: client1");
		exit(1);
	}
	else;

	write(sockfd,&ch,1);	//	POSIX interface
	read(sockfd,&ch,1);	//	POSIX interface
	printf("char from server = %c\n",ch);
	close(sockfd);		//	off socket' file_descriptor
	exit(0);	
}
