#include<unistd.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"shm_com.h"

int main()
{
	int running=1;		//	process run
	void* shared_memory=(void*)0;		//	share_memory' address

	struct shared_use_st* shared_stuff;	//	data ptr

	int shmid;

	srand((unsigned int)getpid());

	shmid=shmget((key_t)1234,sizeof(struct shared_use_st),0666|IPC_CREAT);

	if (shmid == -1)
	{
		fprintf(stderr,"shmget failed\n");
		exit(EXIT_FAILURE);
	}
	else;

	shared_memory=shmat(shmid,(void*)0,0);
	if (shared_memory == (void*)-1)
	{
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}
	else;
	printf("Memory attached at %X\n",shared_memory);	//	%X / %x is 16 binnay

	//	shared_memory' size is struct shared_use_st' size
	//
	

	shared_stuff=(struct shared_use_st*)shared_memory;

	shared_stuff->written_by_you=0;
	
	while (running)
	{	
		if (shared_stuff->written_by_you)
		{
			printf("You wrote: %s",shared_stuff->some_text);
			sleep(rand()%4);	//	wait
			shared_stuff->written_by_you=0;
			
			if (strncmp(shared_stuff->some_text,"end",3) == 0)
				running=0;	
			else;
		}
		else;
	}

	if (shmdt(shared_memory) == -1)
	{
		fprintf(stderr,"shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	else;

	if (shmctl(shmid,IPC_RMID,NULL) == -1)
	{
		fprintf(stderr,"shmctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	else;

	exit(EXIT_SUCCESS);
}
