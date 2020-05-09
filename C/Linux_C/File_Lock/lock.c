#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>

int main(void)
{
	int file_desc,save_errno;
	
	file_desc=open("./lock.tmp",O_RDWR | O_CREAT | O_EXCL, 0444);	// 0444  is mode 0444 is can read of all_user..
									// only_read
	
	if (file_desc == -1)
	{
		save_errno=errno;
		printf("Open failed with error %d \n",save_errno);
	}
	else
	{
		printf("Open succeeded\n");
	}


	exit(EXIT_SUCCESS);
}
