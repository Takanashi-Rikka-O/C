//#include<unistd.h>
//#include<sys/resource.h>
#include<syslog.h>
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	openlog("ROOT",LOG_PID|LOG_CONS,LOG_USER);
	FILE* fp;
	fp=fopen("lop.txt","r");
	if (!fp)
		syslog(LOG_ERR|LOG_USER,"Open file - %m | file: %s\n","lop.txt");
	else;	
	closelog();	


	return 0;
}
