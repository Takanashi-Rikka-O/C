#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

#define ONE_K 1024

int main(void)
{
	char* temp=NULL;
	int Mega=0;

	while (1)
	{
		for (int counter=0; counter < 1024; ++counter)
		{
			temp=(char*)malloc(ONE_K);
			if (temp == NULL) exit(EXIT_FAILURE);
			else sprintf(temp,"Hello World");
		}
		Mega++;
		if (Mega % 128 == 0)
			printf("%s - now allocated %d MegaByte\n",temp,Mega);
		else;
	}

	exit(EXIT_SUCCESS);

}
