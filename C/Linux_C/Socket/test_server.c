#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int s_fd,c_fd;		//	socket descriptor
	int s_len,c_len;	//	socket address long
	struct sockaddr_in s_addr,c_addr;	//	server and client' address

	puts("Server starting..");
	s_fd=socket(AF_INET,SOCK_STREAM,0);
	
	s_addr.sin_family=AF_INET;
	s_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	s_addr.sin_port=htons(34566);
	s_len=sizeof(s_addr);

	bind(s_fd,(struct sockaddr*)&s_addr,s_len);
	listen(s_fd,3);

	//	set prot and listen link of client
	
	puts("Wait client...");
	c_len=sizeof(c_addr);
	c_fd=accept(s_fd,(struct sockaddr*)&c_addr,&c_len);
	puts("Link with client....");
	sleep(10);
	puts("read data..in server");
	int result;
	char kksk;
	result=read(c_fd,&kksk,1);
	if (result == -1)
	{
		perror("read is falied..in server");
		exit(3);
	}
	else
		printf("Get data with %d bytes - %c in server\n",result,kksk);

	kksk+=3;
	puts("Write to socket..");
	result=write(c_fd,&kksk,1);
	if (result == -1)
	{
		perror("write is failed..in server");
		exit(2);
	}
	else
	{
		printf("Wrote is %d bytes - %c \n",result,kksk);
		puts("OFF link in server");
		close(c_fd);
	}

	puts("Work over, server stop..in server");
	close(s_fd);
	puts("Quit...in server");
	sleep(3);

	exit(EXIT_SUCCESS);
}
