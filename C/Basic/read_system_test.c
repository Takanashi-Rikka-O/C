#include<unistd.h>
#include<stdlib.h>

int main(void)
{
	char* bufs=(char*)malloc(10*sizeof(char));
	write(1,"Please input string, long is 9\n",31);
	read(0,bufs,9);
	write(1,bufs,9);
	free(bufs);
	exit (0);
}
