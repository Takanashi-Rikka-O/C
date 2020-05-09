#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void)
{
	const char* temp="./lock.tmp";

	if (unlink(temp) == 0)
	{
		printf("Succeeded\n");
		return 0;
	}
	else
		exit(EXIT_FAILURE);

}
