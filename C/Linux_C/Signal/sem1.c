#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/sem.h>



union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};



static int set_semvalue(void);		//	initialize a semaphore before for first use 
static void del_semvalue(void);		//	delete semaphore
static int semaphore_p(void);		//	semaphore + 1
static int semaphore_v(void);		//	semaphore - 1

static int sem_id;			//	semaphore - variable  (static)

int main(int argc, char* argv[])
{
	int i;
	int pause_time;
	char op_char='o';
	
	srand((unsigned int)getpid());
	
	sem_id=semget((key_t)1234,1,0666|IPC_CREAT);		//	creat semaphore

	if (argc > 1)
	{
		if (!set_semvalue())
		{
			fprintf(stderr,"Failed to initialize semaphore..\n");
			exit(EXIT_FAILURE);
		}
		else;
		op_char='x';
		sleep(2);
	}
	else;

	for (i=0; i<10; ++i)
	{
		if (!semaphore_p())	
			exit(EXIT_FAILURE);
		else;

		putc(op_char,stdout);

		fflush(stdout);

		pause_time=rand()%3;

		sleep(pause_time);

		putc(op_char,stdout);

		fflush(stdout);

		if (!semaphore_v())	
			exit(EXIT_FAILURE);
		else;

		pause_time=rand()%2;

		sleep(pause_time);
	}
	
	printf("\n%d - finished\n",getpid());
	
	if (argc > 1)
	{
		sleep(10);
		del_semvalue();		//	delete semaphore
	}
	else;
	exit(EXIT_SUCCESS);
}


static int set_semvalue(void)
{
	union semun sem_union;
	
	sem_union.val=1;
	if (semctl(sem_id,0,SETVAL,sem_union) == -1)	return 0;
	else;

	return 1;
}

static void del_semvalue(void)
{
	union semun sem_union;
	
	if (semctl(sem_id,0,IPC_RMID,sem_union) == -1)
		fprintf(stderr,"Failed to delete semaphore\n");
	else;
	
}

static int semaphore_p(void)
{
	struct sembuf sem_p;
	
	sem_p.sem_num=0;
	sem_p.sem_op=-1;
	sem_p.sem_flg=SEM_UNDO;
	
	if (semop(sem_id,&sem_p,1) == -1)
	{
		fprintf(stderr,"semphore_p failed\n");
		return 0;
	}
	else;
	
	return 1;
}

static int semaphore_v(void)
{
	struct sembuf sem_v;
	
	sem_v.sem_num=0;
	sem_v.sem_op=1;
	sem_v.sem_flg=SEM_UNDO;
	
	if (semop(sem_id,&sem_v,1) == -1)
	{
		fprintf(stderr,"semphore_v failed\n");
		return 0;
	}
	else;
	
	return 1;
}


