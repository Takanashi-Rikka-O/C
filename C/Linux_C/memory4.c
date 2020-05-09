#include<stdlib.h>
#define ONE_K 104

int main(void)
{
	char *temp, *temp1;

	temp=(char*)malloc(ONE_K);
	if (temp == NULL)
		exit(EXIT_FAILURE);
	else
		temp1=temp;

	while (1)
	{
		*temp1++='\0';

	}



	exit(EXIT_SUCCESS);
}
