#include<sys/socket.h>		//	socket interface
#include<netinet/in.h>		//	struct statment of AF_INET  address 
#include<netdb.h>		//	network database
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>		//	POSIX interface

int main(int argc, char* argv[])
{
	char* host;		//	host name
	int sockfd;		//	socket descriptor
	int len, result;	//	len->address long	result->return information
	struct sockaddr_in address;	//	AF_INET address 
	struct hostent* hostinfo;	//	gethostbyname and gethostbyaddr' return 
	struct servent* servinfo;	//	getservbyname and getservbyport' return
	char buffer[128];		//	buffer
	
	if (argc == 1)
		host="localhost";
	else
		host=argv[1];

	hostinfo=gethostbyname(host);	//	get host_information
	
	if (!hostinfo)
	{
		fprintf(stderr,"no host: %s\n",host);
		exit(1);
	}
	else;

	//	check service daytime in this host
	
	servinfo=getservbyname("daytime","tcp");	//	search service 'daytime'
	if (!servinfo)
	{
		fprintf(stderr,"no daytime service\n");
		exit(2);
	}
	else;

	printf("daytime port is %d\n",ntohs(servinfo->s_port));

	sockfd=socket(AF_INET,SOCK_STREAM,0);		//	create socket and AF_INET SOCK_STREAM TCP/IP
	
	address.sin_family=AF_INET;
	address.sin_port=servinfo->s_port;		//	use daytime' port
	address.sin_addr=*(struct in_addr*)*hostinfo->h_addr_list;
	len=sizeof(address);

	
	result=connect(sockfd,(struct sockaddr*)&address,len);

	if (result == -1)	//	failed?
	{
		perror("oops: getdate");
		exit(3);
	}
	else;

	result=read(sockfd,buffer,sizeof(buffer));
	buffer[result]='\0';
	printf("read %d bytes: %s",result,buffer);
	close(sockfd);
	exit(0);
}
