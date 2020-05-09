#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	#ifdef DEBUG
		printf("Compiled: ");
		printf(_DATE);
		printf(" at ");
		printf(_TIME);
		putchar('\n');
		printf("This is line %d of file %s\n",_LINE,_FILE);
	#endif

	printf("Hello World\n");

	exit(EXIT_SUCCESS);
}
