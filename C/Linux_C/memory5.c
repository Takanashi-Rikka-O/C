#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void)
{
	char* temp=NULL;

	printf("temp == null temp is %s _ string\n",temp);
	sprintf(temp,"Hello World");
	exit(EXIT_SUCCESS);


}
