#include<stdio.h>
#include<stdlib.h>
#include<term.h>
#include<curses.h>

int main(void)
{
	int nlines;
	int ncolses;

	setupterm(NULL,fileno(stdout),NULL);	// setupterm can link current_tty...  program and tty...

	//	setupterm at the failure, can auto interrupt...		parameter_3 is have to  NULL  ..


	// setupterm success, can get some information and can change set..
	
	nlines=tigetnum("lines");
	ncolses=tigetnum("cols");

	// tigetnum can get some number value... "..." is value's flag(name) ..

	printf("This terminal has %d lines, %d colses..\n",nlines,ncolses);
	
	printf("OK : %d\tERR : %d\n",OK,ERR);


	// use the tigetstr() and tparm() , putp();
	
	// char* tigetstr(char* flag);	return  parameter_string..
	
	// char* tparm(char* capname, long p1, long p2, ...);	
	// capname is a parameter_string
	// p1 is parameter_string's first parameter... '%d' 
	// return a escape_string..
	//
	// int putp(char* const escape_str);
	// escape_str write to tty...
	// success return OK(0) , failure return ERR(-1)


	char *cup_str, *es_str;

	cup_str=tigetstr("cup");
	es_str=tparm(cup_str,5,20);	// 5 is lines, 20 is cols..
	
	if (putp(es_str)==ERR)
	{
		fprintf(stderr,"PUTP is error ... \n");
		exit(1);
	}
	else printf("Success...!!\n");

	return 0;
}
