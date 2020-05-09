#include<stdio.h>
#include<stdlib.h>

int main()
{
	char* ptr=(char*)malloc(1024);
	ptr[0]=0;
	
	// Now write beyond the block
	
	ptr[1024]=0;
	
	// The code is test ... not have free()
	exit(0);
}
