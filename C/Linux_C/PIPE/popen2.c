#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
	puts("Now we use the popen and pclose to view this process");

	FILE* kksk;

	kksk=popen("uname -a","r");		//	Open shell to write command and mode is only_read

	char buffer[256];
	memset(buffer,'\0',sizeof(buffer));

	fgets(buffer,256,kksk);
	buffer[strlen(buffer)-1]='\0';
	puts("View read' data");

	puts(buffer);

	puts("quit");

	pclose(kksk);


	exit(EXIT_SUCCESS);
}
