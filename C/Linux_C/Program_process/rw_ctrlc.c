#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void ouch(int sig)
{
	printf("OUCH! - I got signal %d\n",sig);
//	(void) signal(SIGINT,SIG_DFL);
}

int main()
{
//	(void) signal(SIGINT,ouch);

	struct sigaction act;
	
	act.sa_handler=ouch;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
//	act.sa_flags=SA_RESETHAND;	

	sigaction(SIGINT,&act,0);


	while (1)
	{
		printf("Hello World!\n");
		sleep(1);
	}
	return 0;
}
