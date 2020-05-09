#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<termios.h>
#include"mysql.h"


MYSQL connect;		// Link ptr
MYSQL_RES* res_ptr;	// information ptr
MYSQL_ROW sqlrow;	// information-row ptr

void display();

int main(void)
{
	//MYSQL connect;
	//MYSQL_RES* res_ptr;	//	information struct .. 
	//MYSQL_ROW sqlrow;	//	row struct .. 

	int res;

	char* user_name=(char*)malloc(12*sizeof(char));
	char* db_name=(char*)malloc(12*sizeof(char));
	char* passwd=(char*)malloc(12*sizeof(char));
	
	struct termios tmp, new_tmp;

	printf("Initialize -- ..\n");
	mysql_init(&connect);
	sleep(2);
	printf("Please input user-name : ");
	scanf("%s",user_name);
	//scanf("%[^\n]",user_name);
	//getchar();	
	printf("Please input database-name : ");
	scanf("%s",db_name);
	//scanf("%[^\n]",db_name);
	//getchar();
	printf("Please input password : ");
	tcgetattr(fileno(stdin),&tmp);
	new_tmp=tmp;
	new_tmp.c_lflag &= ~ICANON;
	new_tmp.c_lflag &= ~ECHO;
	new_tmp.c_cc[VMIN]=1;
	new_tmp.c_cc[VTIME]=0;
	if (tcsetattr(fileno(stdin),TCSANOW,&new_tmp) != 0)
	{
		fprintf(stderr,"tty set is error..\n");
		exit(EXIT_FAILURE);
	}
	else;
	scanf("%s",passwd);
	//scanf("%[^\n]",passwd);
	//getchar();
	tcsetattr(fileno(stdin),TCSAFLUSH,&tmp);




	if (mysql_real_connect(&connect,"localhost",user_name,passwd,db_name,3306,NULL,0))
		printf("\nConnected...\n");
	else
	{
		fprintf(stderr,"Cannot connect to MySQL .. %d : %s\n",mysql_errno(&connect),mysql_error(&connect));
		mysql_close(&connect);
		exit(3);
	}

	res=mysql_query(&connect,"SELECT childno,fname,age FROM children WHERE age > 1");
	if (res)
		printf("SELECT error: %s\n",mysql_error(&connect));
	else
	{
		res_ptr=mysql_use_result(&connect);
		if (res_ptr)
		{
			//printf("Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
			while ((sqlrow=mysql_fetch_row(res_ptr)))
			{
				printf("Fetched data..\n");
				display();
			}
			if (mysql_errno(&connect))
				fprintf(stderr,"Retrive error: %s\n",mysql_error(&connect));
			else;
			mysql_free_result(res_ptr);
		}
		else
			printf("Cannot extract information \n");
	}

	mysql_close(&connect);
	exit(EXIT_SUCCESS);
}


void display()
{
	unsigned int count=0;
	while (count < mysql_field_count(&connect))
		printf("%s ",sqlrow[count++]);
	putchar('\n');
}

