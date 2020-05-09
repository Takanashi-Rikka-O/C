#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{

	int res=mkfifo("./my_fifo",0777);	//	ALL permission  (0 4 2 1) 	0777 is the file's mode

	if (res == 0)	printf("FIFO created\n");
	else
	{
		perror("FIFO creat failed");
		exit(EXIT_FAILURE);
	}


	exit(EXIT_SUCCESS);
}
