#include<stdio.h>
#include<stdlib.h>

int main()
{
	int i=0;
		
	puts("Please input int_number..");
	while (scanf("%d",&i) == 1)
	{
		printf("Hello World : %d\n",i);
		sleep(2);
		puts("Please input int_number..");
	}


	exit(EXIT_SUCCESS);
}
