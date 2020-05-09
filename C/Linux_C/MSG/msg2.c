#include<unistd.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>


#define MAX_TEXT 512


struct my_msg_st			//	This struct is data' buffer, but first long int - member isn't data.. It's type
{
	long int my_msg_type;
	char some_text[MAX_TEXT];
};


int main()
{
	int running=1;			//	count
	int msgid;			//	message_queue' ID
	struct my_msg_st some_data;	//	data object
//	long int msg_to_receive=0;	//	receive priority

	char buffer[BUFSIZ];		//	data buffer



	msgid=msgget((key_t)1234,0666|IPC_CREAT);		//	creat msg-queue
	
	if (msgid == -1)	//	IF true , msgget failed
	{
		fprintf(stderr,"msgget failed with error: %d\n",errno);
		exit(EXIT_FAILURE);
	}
	else;

	while (running)
	{
		printf("Enter some text : ");
		fgets(buffer,BUFSIZ,stdin);
		some_data.my_msg_type=1;
		strcpy(some_data.some_text,buffer);
		
		if (msgsnd(msgid,(void*)&some_data,MAX_TEXT,0) == -1)		//	IF true , it's failed
		{
			fprintf(stderr,"msgsnd failed\n");
			exit(EXIT_FAILURE);
		}
		else;

		if (strncmp(some_data.some_text,"end",3) == 0)
			running=0;
		else;
	}



	exit(EXIT_SUCCESS);
}
