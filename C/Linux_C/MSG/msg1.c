#include<unistd.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>


struct my_msg_st			//	This struct is data' buffer, but first long int - member isn't data.. It's type
{
	long int my_msg_type;
	char some_text[BUFSIZ];
};


int main()
{
	int running=1;			//	count
	int msgid;			//	message_queue' ID
	struct my_msg_st some_data;	//	data object
	long int msg_to_receive=0;	//	receive priority



	msgid=msgget((key_t)1234,0666|IPC_CREAT);		//	creat msg-queue
	
	if (msgid == -1)	//	IF true , msgget failed
	{
		fprintf(stderr,"msgget failed with error: %d\n",errno);
		exit(EXIT_FAILURE);
	}
	else;

	while (running)
	{
		if (msgrcv(msgid,(void*)&some_data,BUFSIZ,msg_to_receive,0) == -1)	//	IF true, it's failed
		{
			fprintf(stderr,"msgrcv failed with error: %d\n",errno);
			exit(EXIT_FAILURE);
		}
		else;

		printf("You wrote: %s",some_data.some_text);
		if (strncmp(some_data.some_text,"end",3) == 0)
			running=0;
		else;
	}


	if (msgctl(msgid,IPC_RMID,0) == -1)
	{
		sleep(3);
		if (msgctl(msgid,IPC_RMID,0) == -1)
		{
			fprintf(stderr,"msgctl(IPC_RMID) failed\n");
			exit(EXIT_FAILURE);
		}
		else;
	}
	else;




	exit(EXIT_SUCCESS);
}


/*

0666		0001

0666
1110 &

0660


0660
0001 |

0661


1001	0001 ~ 1110

1001
1110 &

1000


1000
0001 |

1001


*/





