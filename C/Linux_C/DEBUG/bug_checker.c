#include<stdio.h>
#include<stdlib.h>

int main()
{
	char* ptr=(char*)malloc(1024);

	// Uninitialized read	

	char ch;
	ch=ptr[1024];

	// Write beyond the block

	ptr[1024]=0;

	// Orphan the block

	ptr=0;

	// BUG Program.....		Not using free() to freed memory.

	exit(0);

}
