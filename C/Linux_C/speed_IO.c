
#define _POSIX_SOURCE
#define _XOPEN_SOURCE


#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<termios.h>

int main(void)
{
	speed_t temp=0;
	struct termios tmp_ter;
	int fp=open("/dev/tty",O_RDWR|O_NOCTTY);	// open's flags in head_file : fcntl.h   ...
	if (fp==-1)
	{
		fprintf(stderr,"The /dev/tty cannot open..\n");
		exit(1);
	}
	else;
	
	tcgetattr(fp,&tmp_ter);
	
	printf("I_speed: %d\n",cfgetispeed(&tmp_ter));
	printf("O_speed: %d\n",cfgetospeed(&tmp_ter));


	printf("We Hang the tty...\n");
	struct termios de_fault;
	de_fault=tmp_ter;	//copy the tty's set...

	temp=B0;
	cfsetispeed(&tmp_ter,temp);
	cfsetospeed(&tmp_ter,temp);

	tcsetattr(fp,TCSANOW,&tmp_ter);	//set tty..

	for (int x=0; x<4; ++x)
	{
		printf(".");
		sleep(1);
	}
	fputc('\n',stderr);

	tcsetattr(fp,TCSANOW,&de_fault);	// reset tty ...
	
	printf("Reset...\n");
	
	if (close(fp)==-1)
	{
		fprintf(stderr,"Can't shutdown /dev/tty ...\n");
		exit(2);
	}
	else printf("done\n");




	return 0;
}
