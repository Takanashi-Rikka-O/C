#define _REENTRANT
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
//#include<string.h>

void* thread_function(void* arg);	//	 thread is start up to this function..
//char message[]="Hello World";		//	 global vaiable.. char array

int main()
{
	int res;
	pthread_t a_thread;	//	thread'identifier
	void* thread_result;	//	thread' return .. 
	
	res=pthread_create(&a_thread,NULL,thread_function,NULL);

	if (res != 0)
	{
		perror("Thread creation failed.. \n");
		fprintf(stderr,"res is %d\n",res);
		exit(EXIT_FAILURE);
	}
	else;

	sleep(3);

	printf("Canceling thread...\n");
	res=pthread_cancel(a_thread);
	if (res != 0)
	{
		perror("Thread cancelation failed..");
		exit(EXIT_FAILURE);
	}
	else printf("Thread -- %lu canceled..\n",a_thread);

	

	printf("Waiting for thread to finish...\n");
	res=pthread_join(a_thread,&thread_result);
	if (res != 0)
	{
		perror("Thread join failed\n");
		exit(EXIT_FAILURE);
	}
	else;

//	printf("Thread joined, itreturned %s\n",(char*)thread_result);
//	printf("Message is now %s\n",message);

	exit(EXIT_SUCCESS);
}

void* thread_function(void* arg)
{
	int i, res;
	res=pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	if (res != 0)
	{
		perror("Thread pthread_setcancelstate failed..");
		exit(EXIT_FAILURE);
	}
	else;

	res=pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
	if (res != 0)
	{
		perror("Thread pthread_setcanceltype failed");
		exit(EXIT_FAILURE);
	}
	else;



	printf("thread_function is running..\n");
	for (i=0; i < 10; ++i)
	{
		printf("Thread is still running (%d)...\n",i);
		sleep(1);
	}









/*
	printf("thread_function is running.Argument was %s\n",(char*)arg);
	sleep(3);
	strcpy(message,"Bye!");
*/

	pthread_exit(NULL);	//	This function can exit for the thread..

}
