#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

int main(void)
{
	char temp;
	int in=0,out=0;
	int close_e=0;
	in=open("fp.txt",O_RDONLY);
	out=open("test_file.txt",O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
	while (read(in,&temp,1)==1)
		{
			if (write(out,&temp,1)==-1)
				{
					write(2,"write error\n",5+2+5);
					exit(1);
				}
			else;
		}
	close_e=close(in);
	if (-1==close_e)
		{
			write(2,"Close in is error\n",5+6+2+5);
			exit(2);
		}
	else close_e=close(out);
	if (-1==close_e)
		{
			write(2,"Close out is error\n",5+6+2+5+1);
			exit(3);
		}
	else;


	return 0;
}
