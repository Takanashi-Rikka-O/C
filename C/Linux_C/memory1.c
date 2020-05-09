#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

#define LONG (1024*1024)

int main(void)
{
	char* temp=NULL;
	temp=(char*)malloc(LONG);
	if (temp==NULL)
	{	
		fprintf(stderr,"Memory error...\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		sprintf(temp,"Hello World");
		puts(temp);
		return 0;
	}
}
