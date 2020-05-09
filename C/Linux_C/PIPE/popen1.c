#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
	puts("Now we use the popen and pclose to view process");

	FILE* kksk;

	kksk=popen("cat","w");	//	open shell and write command 'cat'

	fwrite("Is process",sizeof(char),10,kksk);	//	wrtie data to cat

	puts("Use the pclose off the stream");

	pclose(kksk);
	puts("\nquit..");

	exit(EXIT_SUCCESS);
}
