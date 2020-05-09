#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#define MEMORY (1024*1024)
#define LIMIT 1024

int main(void)
{
	char* temp=NULL;
	int counter=0;

	while (counter < (LIMIT*2))
	{
		temp=(char*)malloc(MEMORY);
		if (temp!=NULL)
		{
			counter++;
			if (counter % 128 == 0)
			{
				sprintf(temp,"Hello World");
				printf("%s - now allocated %d MegaByte\n",temp,counter);
			}

		}
		else exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
