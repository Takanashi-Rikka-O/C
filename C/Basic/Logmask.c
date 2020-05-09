#include<unistd.h>
#include<syslog.h>
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	int logmask;

	openlog("logmask",LOG_PID|LOG_CONS,LOG_USER);
	syslog(LOG_INFO,"informative message, pid= %d",getpid());//getpid() in unistd.h
	syslog(LOG_DEBUG,"debug message,should appear");
	logmask=setlogmask(LOG_UPTO(LOG_NOTICE));// set log priority... below the LOG_NOTICE logs,not write...
	syslog(LOG_DEBUG,"debug message,should not appear");




	return 0;
}
