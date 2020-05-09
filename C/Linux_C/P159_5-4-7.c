#include<termios.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define PASSWORD_LEN 8

int main(void)
{
	struct termios de_fault,new;

	char Password[PASSWORD_LEN+1];

	int f_in=fileno(stdin);

	tcgetattr(f_in,&de_fault);	// this default set..

	new=de_fault;	//copy set

	new.c_lflag&=~ECHO;	// off the echo_set ...
	
	if (tcsetattr(f_in,TCSAFLUSH,&new)!=0)	// set tty
	{
		fprintf(stderr,"Can't set the stdin_echo ... \n");
		exit(1);
	}
	else	printf("Enter password: ");
	
	fgets(Password,PASSWORD_LEN,stdin);

	Password[strlen(Password)-1]='\0';

	if (tcsetattr(f_in,TCSANOW,&de_fault)!=0)	// reset tty
	{
		fprintf(stderr,"Cannot reset the stdin.. please shell.. stty\n");
		exit(2);
	}
	else printf("\nYou entered %s\n",Password);

	return 0;
}
