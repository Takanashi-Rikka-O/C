#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[])
{
	if (argc>1)
	{
		if (strcmp(argv[1],"-h")==0||strcmp(argv[1],"-help")==0)
		{
			printf("Show help manual : \n");
			puts("Thank you use this program, please enjoy youself!!");
			return 0;
		}
		else if (strcmp(argv[1],"-s")==0||strcmp(argv[1],"-stop")==0)
		{
			printf("We show this message...now stop program...\n");
			exit(1);
		}
		else 
		{
			fprintf(stderr,"Don't know this parameter...\n");
			exit(2);
		}

	}
	else 
		printf("Not have parameter...print this message.Showdown program....\n");
	return 0;
}
