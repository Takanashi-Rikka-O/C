#include<stdio.h>
#include<term.h>
#include<curses.h>
#include<stdlib.h>

int main(void)
{

	setupterm("unlisted",fileno(stdout),0);
	
	printf("Done.\n");

	return 0;
}
