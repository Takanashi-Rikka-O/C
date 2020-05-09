#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>		//	network database
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
	char *host,**names,**addrs;	//	host, name, address
	struct hostent *hostinfo;	//	host data 
	
	if (argc == 1)
	{
		char myname[256];
		gethostname(myname,256);	//	interface to get host name.	Could get the current hostname
		host=myname;
	}
	else
		host=argv[1];
	
	hostinfo=gethostbyname(host);		//	This interface can get host' information, and write to the struct.

	if (!hostinfo)			//	hostinfo == NULL, the interface is false. failed
	{
		fprintf(stderr,"Cannot get info for host: %s\n",host);
		exit(1);
	}
	else;

	printf("results for host %s:\n",host);		//	View information of the host
	printf("Name: %s\n",hostinfo->h_name);
	printf("Aliases:");
	names=hostinfo->h_aliases;
	while (*names)		//	names->h_aliases.. cycle and to show list of aliases..
	{
		printf(" %s ",*names++);
		//	aliases is NULL to end
	}
	
	putchar('\n');

	if (hostinfo->h_addrtype != AF_INET)		//	if address is not a IP_address
	{
		fprintf(stderr,"not an IP host\n");
		exit(2);
	}
	else;

	addrs=hostinfo->h_addr_list;		//	h_addr_list is list of the address.. null to end
	while (*addrs)
	{
		printf(" %s \n",inet_ntoa(*(struct in_addr*)*addrs));	//	inet_ntoa return a char*
		// inet_ntoa' parameter is a value.. It's a struct.. 
		addrs++;
	}
	putchar('\n');
	exit(0);
}
