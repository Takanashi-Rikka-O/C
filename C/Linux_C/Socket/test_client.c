#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int c_fd;
	int result;
	char kksk='S';
	struct sockaddr_in s_addr;
	int s_len;

	puts("Client open socket to link..");
	c_fd=socket(AF_INET,SOCK_STREAM,0);
	
	s_addr.sin_family=AF_INET;
	s_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	s_addr.sin_port=htons(34566);
	s_len=sizeof(s_addr);

	puts("Client to link with server..");
	result=connect(c_fd,(struct sockaddr*)&s_addr,s_len);
	if (result == 0)
		printf("Link success..\n");
	else
	{
		perror("Link failed..in client");
		exit(5);
	}

	puts("write...");
	result=write(c_fd,&kksk,1);
	if (result == -1)
	{
		perror("write failed..in client");
		exit(2);
	}
	else;
	puts("read...");
	result=read(c_fd,&kksk,1);
	if (result == -1)
	{
		perror("read failed..in client");
		exit(3);
	}
	else
		printf("read %d bytes - %c\n",result,kksk);


	puts("Work over .. stop link..in client");
	close(c_fd);

	exit(EXIT_SUCCESS);
	
}
