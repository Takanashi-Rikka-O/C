
#define _REENTRANT

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void* thread_function(void* arg);

char message[]="Hello World";
int thread_finished=0;		//	FLAG. when the sub_thread is over to change it

int main()
{
	int res;
	pthread_t a_thread;	//	thread's flag.. & 
	pthread_attr_t thread_attr;	//	thread's attributes
	
	res=pthread_attr_init(&thread_attr);
	if (res != 0)
	{
		perror("Attribute creation failed..");
		exit(EXIT_FAILURE);
	}
	else	puts("Attr initialize success...");

	res=pthread_attr_setdetachstate(&thread_attr,PTHREAD_CREATE_DETACHED);		//	set detach thread_attr
	if (res != 0)
	{
		perror("Attr set to detached, failed...");
		exit(EXIT_FAILURE);
	}
	else	puts("Change to detach for attr...");
	
	res=pthread_create(&a_thread,&thread_attr,thread_function,(void*)message);
	if (res != 0)
	{
		perror("Thread is create failed....");
		exit(EXIT_FAILURE);
	}
	else printf("Thread -- %lu start\n",a_thread);
	
	(void)pthread_attr_destroy(&thread_attr);	//	delete attr_variable
	
	while (!thread_finished)
	{
		printf("Wating for thread to say it's finished..\n");
		sleep(1);
	}

	printf("Other thread finished, bye..\n");

	exit(EXIT_SUCCESS);
}


void* thread_function(void* arg)
{
	printf("thread_function is running. Argument was %s\n",(char*)arg);
	sleep(4);
	printf("Second thread setting finished flag, and exiting now..\n");
	thread_finished=1;
	pthread_exit(NULL);
}

