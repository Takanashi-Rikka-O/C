#include<unistd.h>
#include<sys/utsname.h>
//#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>


int main(void)
{
	char* net_name=(char*)malloc(16*sizeof(char));
	puts("We use the gethostname() ..");

	if (gethostname(net_name,15)==-1)
	{
		fprintf(stderr,"Can't give the net-name...\n");
		exit(1);
	}
	else
		printf("NET-NAME : %s\n",net_name);
	free(net_name);



	puts("We use the uname()...");
	struct utsname* u_name=(struct utsname*)malloc(1*sizeof(struct utsname));// open memory


	if (uname(u_name)==-1)
	{
		fprintf(stderr,"uname() is error...\n");
		exit(2);
	}
	else
		printf("sysname: %s\nnodename: %s\nrelease: %s\nversion: %s\nmachine: %s\n",
		u_name->sysname,u_name->nodename,u_name->release,u_name->version,u_name->machine);
	free(u_name);

	
	puts("Now we use the gethostid()...\n");

	long int H_ID=0;//return ...

	H_ID=gethostid();//use the function..

	printf("The Host-ID: %ld\n",H_ID);

	return 0;
}
