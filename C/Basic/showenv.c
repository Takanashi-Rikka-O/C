#include<stdio.h>
#include<stdlib.h>

extern char** environ;


int main(void)
{
	char** tmp=environ;

	while (*tmp)
	{

	printf("%s\n",*tmp++);

	}



	return 0;
}
