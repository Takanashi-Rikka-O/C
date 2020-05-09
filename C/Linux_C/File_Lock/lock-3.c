#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>

const char* file_path="./lock-3.tmp";

int main(void)
{
	int file_desc, byte_count;	// file's desc and count

	char* byte_to_write="A";	// write char

	struct flock regoin1;	// set_information
	struct flock regoin2;

	int res;	// return _ test
	
	file_desc=open(file_path,O_RDWR | O_CREAT,0666);	// FILE can read and write 0666

	if (!file_desc)
	{
		fprintf(stderr,"Unable to open %s for read/write \n",file_path);
		exit(EXIT_FAILURE);
	}
	else;

	for (byte_count=0; byte_count < 100; ++byte_count)
		(void)write(file_desc,byte_to_write,1);
	
//	------------------	lock information

	regoin1.l_type=F_RDLCK;
	regoin1.l_whence=SEEK_SET;
	regoin1.l_start=10;
	regoin1.l_len=20;
	

	regoin2.l_type=F_WRLCK;
	regoin2.l_whence=SEEK_SET;
	regoin2.l_start=40;
	regoin2.l_len=10;

//	------------------	lock information

	printf("Process %d locking file\n",getpid());

	res=fcntl(file_desc,F_SETLK,&regoin1);
	if (res == -1)
		fprintf(stderr,"Failed to lock regoin1\n");
	else;

	res=fcntl(file_desc,F_SETLK,&regoin2);
	if (res == -1)
		fprintf(stderr,"Failed to lock regoin2\n");
	else;

	sleep(60);
	
	printf("Process %d closing file\n",getpid());
	close(file_desc);	
	
	exit(EXIT_SUCCESS);
}
