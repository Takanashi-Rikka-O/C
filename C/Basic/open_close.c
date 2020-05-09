#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

int main(void)
{
	int open_e=0,write_e=0,read_e=0,close_e=0;
	int fildes=0;
	char* tmp_str=(char*)malloc(12*sizeof(char));
	// 0 input, 1 put, 2 error_put.
	if ((write(1,"Test\n",2+3))==-1)
	{
		write(2,"error\n",3+3);
		exit(1);
	}
	else write(1,"Please input string : ",17+5);
	if ((read_e=read(0,tmp_str,11))==-1)
	{
		write(2,"read_error\n",5+6);
		exit(2);
	}
	else write(1,tmp_str,read_e);
	open_e=open("fp.txt",O_WRONLY|O_EXCL|O_CREAT,S_IRUSR|S_IWUSR);
	if (-1==open_e)
	{
		write(2,"open error\n",11);
		exit(3);
	}
	else;
	write_e=write(open_e,tmp_str,read_e);
	if (-1==write_e)
	{	
		write(2,"write to open-file is error\n",9+9+10);
		exit(4);
	}
	else close_e=close(open_e);
	if (-1==close_e)
	{
		write(2,"close error\n",5+6);
		exit(5);
	}
	else;
	free(tmp_str);
	exit(0);
}
