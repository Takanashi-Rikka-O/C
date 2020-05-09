#include<stdlib.h>
#include<stdio.h>
#include"mysql.h"

int main(int argc, char* argv[])
{
	MYSQL* connect_ptr;
	connect_ptr=mysql_init(NULL);	//	MYSQL* mysql_init(MYSQL*);
	if (!connect_ptr)
	{
		fprintf(stderr,"SQL can't init \n");
			exit(EXIT_FAILURE);
	}
	else;

	unsigned int timeout=5;
	if (mysql_options(connect_ptr,MYSQL_OPT_CONNECT_TIMEOUT,(const char*)&timeout) != 0)
	{
		fprintf(stderr,"Link option - TIMEOUT unset\n");
	}
	else	fprintf(stdout,"Link option - TIMEOUT setted\n");


	connect_ptr=mysql_real_connect(connect_ptr,"localhost","rick","Yukino","rick",0,NULL,0);

	/*
 	MYSQL* mysql_real_connect(MYSQL* connect_ptr,const char* server_host,const char* sql_user_name,
					const char* sql_password,const char* db_name,
					unsigned int port_number,const char* unix_socket_name,
					unsigned int flags);
	failed return NULL;
	*/
	

	if (!connect_ptr)
		printf("Link FAILED\n");
	else
		printf("Link SUCCESS\n");

	mysql_close(connect_ptr);
	//	open and off are matters,proper use....



	exit(EXIT_SUCCESS);
}
