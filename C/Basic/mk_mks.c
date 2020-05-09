
#define _XOPEN_SOURCE
#define _GNU_SOURCE

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(void)
{

	char file_name[7]="XXXXXX";

//	char* file_name=(char*)malloc(7*sizeof(char));
//	for (int x=0; x<7; ++x)
//		file_name[x]='X';
	char* re_name;
	re_name=mktemp(file_name);
	printf("show file_name and re_name : \n");
	printf("address: %p\t%p\n",file_name,re_name);
	printf("string: %s\t%s\n",file_name,re_name);
	
	int b=0;
	printf("use the mkestemp....\n");
	b=mkstemp(file_name);
	printf("re_file_int is b : %d\n",b);
	close(b);


	return 0;
}
