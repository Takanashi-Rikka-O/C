#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>

const char* file_path="./lock-3.tmp";

#define SIZE_TO_TRY 5

void show_lock(struct flock* to_show);

int main(void)
{
	int file_desc, res, start_byte;
	struct flock regoin;

	file_desc=open(file_path,O_RDWR | O_CREAT,0666);

	if (!file_desc)
	{
		fprintf(stderr,"Unable to open %s for read/write",file_path);
		exit(EXIT_FAILURE);
	}
	else;

	for (start_byte=0; start_byte < 99; start_byte+=SIZE_TO_TRY)
	{
	//	-------------------------	lock information test

		regoin.l_type=F_WRLCK;
		regoin.l_whence=SEEK_SET;
		regoin.l_start=start_byte;
		regoin.l_len=SIZE_TO_TRY;
		regoin.l_pid=-1;

	//	-------------------------	lock information test

	printf("Testing F_WRLCK on regoin from %d to %d\n",start_byte,start_byte+SIZE_TO_TRY);
	res=fcntl(file_desc,F_GETLK,&regoin);
	if (-1 == res)
	{
		fprintf(stderr,"F_GETLK failed\n");
		exit(EXIT_FAILURE);
	}
	else;

	if (regoin.l_pid != -1)
	{
		printf("Lock would fail. F_GETLK returned: \n");
		show_lock(&regoin);
	}
	else
		printf("F_WRLCK - Lock would succeed\n");//Regoin->pid : %d\n",regoin.l_pid);

	
	//	-------------------------	lock information test

	regoin.l_type=F_RDLCK;
	regoin.l_whence=SEEK_SET;
	regoin.l_start=start_byte;
	regoin.l_len=SIZE_TO_TRY;
	regoin.l_pid=-1;

	//	-------------------------	lock information test

	printf("Testing F_RDLCK on regoin from %d to %d\n",start_byte,start_byte+SIZE_TO_TRY);
	res=fcntl(file_desc,F_GETLK,&regoin);
	if (-1 == res)
	{
		fprintf(stderr,"F_GETLK failed\n");
		exit(EXIT_FAILURE);
	}
	else;

	if (regoin.l_pid != -1)
	{
		printf("Lock would fail. F_GETLK returned: \n");
		show_lock(&regoin);
	}
	else
		printf("F_RDLCK - Lock would succeed\n");//Regoin->pid : %d\n",regoin.l_pid);
	}

	(void)close(file_desc);	

	exit(EXIT_SUCCESS);
}


void show_lock(struct flock* to_show)
{
	printf("\tl_type %d, ",to_show->l_type);
	printf("l_whence %d, ",to_show->l_whence);
	printf("l_start %d, ",to_show->l_start);
	printf("l_len %d, ",to_show->l_len);
	printf("l_pid %d\n",to_show->l_pid);
}


