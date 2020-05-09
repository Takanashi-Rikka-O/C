#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>

#define PA_TH "./lock1.tmp"

int main(void)
{
	int file_desc, tries=10;
	
	while (tries--)
	{	
		file_desc=open(PA_TH,O_RDWR | O_CREAT | O_EXCL,0444);	// mode 0444 is can read of all user
		if (-1 == file_desc)
		{
			printf("%d - Lock already present\n",getpid());
			sleep(3);
		}
		else	//Critical Regoin ... 
		{
			printf("%d - I have exclusive access\n",getpid());
			sleep(1);
			(void)close(file_desc);
			(void)unlink(PA_TH);
			sleep(2);
		}
	}
	exit(EXIT_SUCCESS);
}
