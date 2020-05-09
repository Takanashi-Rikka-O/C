#include<stdlib.h>
#include<stdio.h>
#include<curses.h>
#include"mysql.h"

int main(void)
{
	MYSQL connect;
	char* server_name=(char*)malloc(12*sizeof(char));
	char* db_name=(char*)malloc(10*sizeof(char));
	char* name=(char*)malloc(10*sizeof(char));
	char* passwd=(char*)malloc(20*sizeof(char));

	int res; // res is return value;

	if (!mysql_init(&connect))
	{
		fprintf(stderr,"MySQL init failed .. \n");
		free(server_name);
		free(db_name);
		free(name);
		free(passwd);
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
	
	if (mysql_real_connect(&connect,server_name,name,passwd,db_name,3306,NULL,CLIENT_FOUND_ROWS))
	// old report

//	if (mysql_real_connect(&connect,server_name,name,passwd,db_name,3306,NULL,0))
	{
		printf("Login SUCCESS!\n");
		
	//	res=mysql_query(&connect,"INSERT INTO children(fname,age) VALUES('Ann',3)"); //success return 0 otherwise not 0

		res=mysql_query(&connect,"UPDATE children SET age=4 WHERE fname='Ann'");

		if (!res)
			printf("Inserted %lu rows\n",(unsigned long)mysql_affected_rows(&connect));
		else
			fprintf(stderr,"Insert error %d : %s\n",mysql_errno(&connect),mysql_error(&connect));


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

	exit(EXIT_SUCCESS);
}
