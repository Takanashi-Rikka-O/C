#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>

const char* file_path="./lock-3.tmp";

int main(void)
{
	int file_desc, res;
	struct flock region;

	file_desc=open(file_path,O_RDWR | O_CREAT,0666);	//	read and write
	
	if (!file_desc)
	{
		fprintf(stderr,"Unable to open %s for read/write\n",file_path);
		exit(EXIT_FAILURE);
	}
	else;

	//	-------------------------	lock information
	
	region.l_type=F_RDLCK;
	region.l_whence=SEEK_SET;
	region.l_start=10;
	region.l_len=5;

	//	-------------------------	lock information
	printf("Process %d, trying F_RDLCK, regoin %d to %d\n",getpid(),region.l_start,region.l_start+region.l_len);
	res=fcntl(file_desc,F_SETLK,&region);	//	Lock
	if (res == -1)
		printf("Process %d - failed to lock regoin\n",getpid());
	else
		printf("Process %d - obtained lock regoin\n",getpid());

	//	-------------------------	lock information
	
	region.l_type=F_UNLCK;
	region.l_whence=SEEK_SET;
	region.l_start=10;
	region.l_len=5;

	//	-------------------------	lock information
	printf("Process %d, trying F_UNLCK, regoin %d to %d\n",getpid(),region.l_start,region.l_start+region.l_len);
	res=fcntl(file_desc,F_SETLK,&region);
	if (res == -1)
		printf("Process %d - failed to unlock regoin\n",getpid());
	else
		printf("Process %d - unlocked regoin\n",getpid());

	
	//	-------------------------	lock information
	
	region.l_type=F_UNLCK;
	region.l_whence=SEEK_SET;
	region.l_start=0;
	region.l_len=50;	

	//	-------------------------	lock information
	printf("Process %d, trying F_UNLCK,region %d to %d\n",getpid(),region.l_start,region.l_start+region.l_len);
	res=fcntl(file_desc,F_SETLK,&region);
	if (res == -1)
		printf("Process %d - failed to unlock region\n",getpid());
	else
		printf("Process %d - unlocked region\n",getpid());

	
	//	-------------------------	lock information
	
	region.l_type=F_WRLCK;
	region.l_whence=SEEK_SET;
	region.l_start=16;
	region.l_len=5;
	
	//	-------------------------	lock information
	printf("Process %d tyring F_WRLCK, region %d to %d\n",getpid(),region.l_start,region.l_start+region.l_len);
	res=fcntl(file_desc,F_SETLK,&region);
	if (res == -1)
		printf("Process %d - failed to lock region\n");
	else
		printf("Process %d - obtained lock on region\n",getpid());


	//	-------------------------	lock information
	
	region.l_type=F_RDLCK;
	region.l_whence=SEEK_SET;
	region.l_start=40;
	region.l_len=10;

	//	-------------------------	lock information
	printf("Process %d, trying F_RDLCK, region %d to %d\n",getpid(),region.l_start,region.l_start+region.l_len);
	res=fcntl(file_desc,F_SETLK,&region);
	if (res == -1)
		printf("Process %d - failed to lock region\n",getpid());
	else
		printf("Process %d - obtained lock on region\n",getpid());

	

	//	-------------------------	lock information

	region.l_type=F_WRLCK;
	region.l_whence=SEEK_SET;
	region.l_start=16;
	region.l_len=5;

	//	-------------------------	lock information
	printf("Process %d, trying F_WRLCK with wait,  region %d to %d\n",getpid(),region.l_start,region.l_start+region.l_len);
	res=fcntl(file_desc,F_SETLKW,&region);
	if (res == -1)
		printf("Process %d - failed to lock region\n",getpid());
	else
		printf("Process %d - obtained lock on region\n",getpid());

	printf("Process %d ending\n",getpid());
	
	(void)close(file_desc);

	
	exit(EXIT_SUCCESS);
}
