#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(void)
{
	int filede=0;
	write(1,"Now we open a file,in current folder..\n",39);
	filede=open("./llls",O_WRONLY|O_TRUNC);
	if (filede==-1)
		{
			write(1,"Open error\n",11);
			//free(buffer);
			exit(1);
		}
	else;
	char* buffer=(char*)malloc(20*sizeof(char));
	int nread=0;
	nread=read(0,buffer,19);
	write(filede,buffer,nread);
	free(buffer);
	exit(0);
}
