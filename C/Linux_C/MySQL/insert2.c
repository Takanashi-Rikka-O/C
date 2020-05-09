#include<stdlib.h>
#include<stdio.h>
#include<curses.h>
#include<string.h>
#include"mysql.h"

int main(void)
{
	MYSQL connect;
	char* server_name=(char*)malloc(12*sizeof(char));
	char* db_name=(char*)malloc(10*sizeof(char));
	char* name=(char*)malloc(10*sizeof(char));
	char* passwd=(char*)malloc(20*sizeof(char));

	int res; // res is return value;

	MYSQL_RES* res_ptr;
	MYSQL_ROW sqlrow;


	char* insert_str=(char*)malloc(72*sizeof(char));
	char* fname=(char*)malloc(15*sizeof(char));

//	char* temp=NULL;

	memset(insert_str,'\0',sizeof(insert_str));
	memset(fname,'\0',sizeof(fname));


	if (!mysql_init(&connect))
	{
		fprintf(stderr,"MySQL init failed .. \n");
		free(server_name);
		free(db_name);
		free(name);
		free(passwd);
		free(insert_str);
		free(fname);
		exit(EXIT_FAILURE);
	}
	else
		printf("MySQL init succeed .. \n");
	initscr();

	printw("Please input server-name : ");
	refresh();
	getnstr(server_name,11);

	printw("Please input database-name : ");
	refresh();
	getnstr(db_name,9);

	printw("Please input user-name : ");
	refresh();
	getnstr(name,9);

	printw("Please input password : ");
	refresh();
	cbreak();
	noecho();
	getnstr(passwd,19);
	nocbreak();
	echo();

	endwin();

	printf("Please input want to insert fname : ");
	scanf("%s",fname);
	getchar();
	printf("Please enter age : ");
	int age=getchar();
	sprintf(insert_str,"INSERT INTO children(fname,age) VALUES('%s',%d)",fname,age);
	//printf("insert_str : %s\n",insert_str);
	//int x=strlen(insert_str);
	//int count=0;
	//char temp[x];
	/* while (*insert_str)
		temp[count++]=*insert_str++;
	*/
//	temp=(char*)realloc(insert_str,strlen(insert_str)+1);


//	reset pointer' size  use the realloc() ;
	
	
	if (mysql_real_connect(&connect,server_name,name,passwd,db_name,3306,NULL,CLIENT_FOUND_ROWS))
	// old report

//	if (mysql_real_connect(&connect,server_name,name,passwd,db_name,3306,NULL,0))
	{
		printf("Login SUCCESS!\n");
		
	//	res=mysql_query(&connect,"INSERT INTO children(fname,age) VALUES('Ann',3)"); //success return 0 otherwise not 0
	
	//	res=mysql_query(&connect,"UPDATE children SET age=4 WHERE fname='Ann'");
/*		if (!res)
			printf("Inserted %lu rows\n",(unsigned long)mysql_affected_rows(&connect));
		else
			fprintf(stderr,"Insert error %d : %s\n",mysql_errno(&connect),mysql_error(&connect));
*/

			if (0 == mysql_query(&connect,insert_str))
				printf("Insert success...\n");
			else
				printf("Insert failed...\n");

		res=mysql_query(&connect,"SELECT LAST_INSERT_ID()");
		if (res)
			printf("SELECT error: %s\n",mysql_error(&connect));
		else
		{
			res_ptr=mysql_use_result(&connect);
			if (res_ptr)
			{
				while ((sqlrow=mysql_fetch_row(res_ptr)))
				// mysql_ferch_row have a MYSQL* ,return a MYSQL struct..
				{
					printf("We inserted childno %s\n",sqlrow[0]);
				}
				mysql_free_result(res_ptr);
			}

		}


		mysql_close(&connect);
	}
	else
	{
		fprintf(stderr,"Connection failed!\n");
		fprintf(stderr,"Connection error %d : %s\n",mysql_errno(&connect),mysql_error(&connect));
	}
	
	free(server_name);
	free(db_name);
	free(name);
	free(passwd);	
	free(insert_str);
	free(fname);
	//free(temp);
	exit(EXIT_SUCCESS);
}
