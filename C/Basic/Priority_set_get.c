#include<unistd.h>
#include<sys/resource.h>
#include<stdio.h>
int main(void)
{
	puts("Test the priority...");
	printf("This process is %d ...\n",getpriority(PRIO_USER,getuid()));

	puts("Now we setpriority to +2 ... ");
	if (setpriority(PRIO_USER,getuid(),+2)==-1)
		printf("Set is error...\n");
	else
		printf("Set is success...\n");
	printf("Set_ getpriority is : %d\n",getpriority(PRIO_USER,getuid()));
	
	return 0;
}
