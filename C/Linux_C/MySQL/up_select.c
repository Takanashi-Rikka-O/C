#include<unistd.h>
#include<termios.h>
#include<stdio.h>
#include<stdlib.h>
#include"mysql.h"


MYSQL connect;
MYSQL_RES* res_ptr;
MYSQL_ROW sqlrow;

void display_header();
void display_row();


int main(void)
{
	int res;
	int first_row=1;	// Used to ensure we display the row header exactly once when data is successfully retrieved

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
		free(user_name);
		free(db_name);
		free(passwd);
		exit(EXIT_FAILURE);
	}
	else;
	scanf("%s",passwd);
	//scanf("%[^\n]",passwd);
	//getchar();
	tcsetattr(fileno(stdin),TCSAFLUSH,&tmp);

	mysql_init(&connect);	//	init

	if (mysql_real_connect(&connect,"localhost",user_name,passwd,db_name,3306,NULL,0))
	{
		printf("\nConnection success..\n");
		res=mysql_query(&connect,"SELECT childno,fname,age FROM children WHERE age > 1");
	
		if (res)
			fprintf(stderr,"SELECT error: %s\n",mysql_error(&connect));
		else
		{
			res_ptr=mysql_use_result(&connect);
			if (res_ptr)
			{
				printf("Extract --- \n");

				while (sqlrow=mysql_fetch_row(res_ptr))
				{
					if (first_row)
					{
						display_header();
						first_row=0;
					}
					else;
					display_row();
				}

				if (mysql_errno(&connect))
					fprintf(stderr,"Retrive error: %s\n",mysql_error(&connect));
				else;
				
				mysql_free_result(res_ptr);	//	free - res_ptr
			}
			else
				fprintf(stderr,"res_ptr is NULL\n");
		}
		mysql_close(&connect);
	}
	else
	{
		fprintf(stderr,"Connection failed\n");
		if (mysql_errno(&connect))
			fprintf(stderr,"Connection error %d: %s\n",mysql_errno(&connect),mysql_error(&connect));
		else;
	}


	free(user_name);
	free(db_name);
	free(passwd);

	exit(EXIT_SUCCESS);
}


void display_header()
{
	MYSQL_FIELD* field_ptr;	//	struct

	printf("Column details: \n");
	while ((field_ptr=mysql_fetch_field(res_ptr)) != NULL)
	{
		printf("\t Name: %s\n",field_ptr->name);
		printf("\t Type: ");
		if (IS_NUM(field_ptr->type))
			printf("Numeric field\n");
		else
		{
			switch (field_ptr->type)
			{
				//case FIELD_TYPE_DECIMAL:
				case FIELD_TYPE_LONG:	
					printf("LONG\n");
					break;
				//case FIELD_TYPE_STRING:
				case FIELD_TYPE_VAR_STRING:
					printf("VARCHAR\n");
					break;
				default:
					printf("Type is %d, check in mysql_com.h\n",field_ptr->type);
					break;
			}
		
		}
		printf("\t Max width %ld\n",field_ptr->length);
			
		if (field_ptr->flags & AUTO_INCREMENT_FLAG)	
			printf("\t Auto increments\n");	
		else;
		putchar('\n');
	}
}

void display_row()
{
	unsigned int field_count=0;
	while (field_count < mysql_field_count(&connect))
	{
		if (sqlrow[field_count])
			printf("%s ",sqlrow[field_count]);
		else printf("NULL");
		field_count++;
	}
	putchar('\n');
}
