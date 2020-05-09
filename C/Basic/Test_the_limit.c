#include<sys/types.h>
#include<sys/resource.h>
#include<sys/time.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void work(void);

int main(void)
{
	struct rusage r_usage;

	//struct rusage have struct ru_utime and struct ru_stime .. 

	struct rlimit r_limit;
	int priority;
	
	work();
	getrusage(RUSAGE_SELF,&r_usage);// get the rusage.. utime and stime
	
	printf("CPU usage: User = %ld.%06ld, System = %ld.%06ld\n",
		r_usage.ru_utime.tv_sec,r_usage.ru_utime.tv_usec,
		r_usage.ru_stime.tv_sec,r_usage.ru_stime.tv_usec);

	priority=getpriority(PRIO_PROCESS,getpid());//get the priority..
	printf("Current priority = %d\n",priority);
	
	getrlimit(RLIMIT_FSIZE,&r_limit);//get the system limit  cur and max..
	printf("Current FSIZE limit: soft = %ld, hard = %ld\n",r_limit.rlim_cur,r_limit.rlim_max);//rlim_t is int or long int

	r_limit.rlim_cur=2048;
	r_limit.rlim_max=4096;

	printf("Setting a 2k file size limit\n");
	setrlimit(RLIMIT_FSIZE,&r_limit);//set the system limit  cur and max..

	work();

	return 0;
}

void work()
{
	FILE* f;
	int i;
	double x=4.5;

	f=tmpfile();// tmpfile return FILE*

	for (i=0; i<10000; i++)
	{
		fprintf(f,"Do some output\n");
		if (ferror(f))
		{
			fprintf(stderr,"Error writing to temporary file \n");
			exit(1);
		}
		else;
	}

	for (i=0; i<1000000; i++)
		x=log(x*x+3.21);// log in the math.h , is a function..
}
