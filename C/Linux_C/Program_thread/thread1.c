#define _REENTRANT
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void* thread_function(void* arg);	//	 thread is start up to this function..
char message[]="Hello World";		//	 global vaiable.. char array

int main()
{
	int res;
	pthread_t a_thread;	//	thread'identifier
	void* thread_result;	//	thread' return .. 
	
	res=pthread_create(&a_thread,NULL,thread_function,(void*)message);

	if (res != 0)
	{
		perror("Thread creation failed.. \n");
		fprintf(stderr,"res is %d\n",res);
		exit(EXIT_FAILURE);
	}
	else;

	printf("Waiting for thread to finish...\n");
	res=pthread_join(a_thread,&thread_result);
	if (res != 0)
	{
		perror("Thread join failed\n");
		exit(EXIT_FAILURE);
	}
	else;

	printf("Thread joined, itreturned %s\n",(char*)thread_result);
	printf("Message is now %s\n",message);
	exit(EXIT_SUCCESS);
}

void* thread_function(void* arg)
{
	printf("thread_function is running.Argument was %s\n",(char*)arg);
	sleep(3);
	strcpy(message,"Bye!");
	pthread_exit("Thank you for the CPU time");	//	This function can exit for the thread..
}
