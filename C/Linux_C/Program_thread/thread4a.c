#define _REENTRANT
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<semaphore.h>


void* thread_function(void* arg);	//	 thread is start up to this function..
//char message[]="Hello World";		//	 global vaiable.. char array
//int run_now;

sem_t bin_sem;				//	 binary_signal ... bin_sem 0 or 1

#define WORK_SIZE 1024

char work_area[WORK_SIZE];


int main()
{
//	run_now=1;
//	int print_count1=0;


	int res;		//	Test_value
	pthread_t a_thread;	//	thread'identifier
	void* thread_result;	//	thread' return .. 
	
	res=sem_init(&bin_sem,0,0);	//	exclusive value=0

	if (res != 0)
	{	
		perror("Semaphore initialization failed");
		exit(EXIT_FAILURE);
	}
	else
		puts("Binary_signal -- bin_sem inited");

	res=pthread_create(&a_thread,NULL,thread_function,NULL);
	/*
	while (print_count1++ < 20)
	{
	//	puts("Now is in main");
		if (run_now == 1)
		{
			printf("1");
			run_now=2;
		}
		else
			sleep(1);

	}
	*/
	if (res != 0)
	{
		perror("Thread creation failed.. \n");
		fprintf(stderr,"res is %d\n",res);
		exit(EXIT_FAILURE);
	}
	else;
	printf("Input some text. Enter 'end' to finish\n");
	while (strncmp("end",work_area,3) != 0)
	{	
		if (strncmp(work_area,"FAST",4) == 0)
		{
			sem_post(&bin_sem);
			strcpy(work_area,"Wheeee....");
		}
		else
		{
			fgets(work_area,WORK_SIZE,stdin);
			sem_post(&bin_sem);	//	binary_signal -- bin_sem+=1
			//printf("Input some text. Enter 'end' to finish\n");
		}
	}

	printf("\nWaiting for thread to finish...\n");
	res=pthread_join(a_thread,&thread_result);
	if (res != 0)
	{
		perror("Thread join failed\n");
		exit(EXIT_FAILURE);
	}
	else;
	printf("Thread joined .. \n");
	
	sem_destroy(&bin_sem);		//	delete the binary_signal -- bin_sem
					//	If has one thread use the bin_sem now, can not delete this binary_signal,fail..


	
//	printf("Message is now %s\n",message);
	exit(EXIT_SUCCESS);
}

void* thread_function(void* arg)
{
	sem_wait(&bin_sem);	//	wait this bin_sem, if it is not 0, bin_sem-=1.. otherwise, wait this bin_sem is not 0

	while (strncmp("end",work_area,3) != 0)
	{
		printf("You input %d characters\n",strlen(work_area)-1);
		sem_wait(&bin_sem);
	}


	//int print_count2=0;
	/*
	while (print_count2++ < 20)
	{
	//	puts("Now is in thread");
		if (run_now == 2)
		{
			printf("2");
			run_now=1;
		}
		else
			sleep(1);
	}
	*/
//	printf("thread_function is running.Argument was %s\n",(char*)arg);
//	sleep(3);
//	strcpy(message,"Bye!");
	pthread_exit(NULL);	//	This function can exit for the thread..
}
