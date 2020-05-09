#include<unistd.h>
#include<stdlib.h>

int main(void)
{
	char* buffer=(char*)malloc(128*sizeof(char));
	int nread;
	nread=read(0,buffer,128);
	if (nread==-1)
		write(2,"A read error has occurred\n",26);
	else;
	
	if ((write(1,buffer,nread))!=nread)
		write(2,"A write error has occurred\n",27);
	free(buffer);
	exit(0);
}
