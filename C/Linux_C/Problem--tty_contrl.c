#include<stdio.h>
#include<stdlib.h>
// #include<conio.h>  Linux is not have conio.h ...
#include<unistd.h>
#include<termios.h>
#include<term.h>
#include<curses.h>


static FILE* output_stream=(FILE*)0;


char* menu[]={
	"a - add new record",
	"d - delete record",
	"q - quit",
	NULL};



//	/dev/tty is link the Current Sesion ... (Use the tty now ... Command_Prompt ) 




/*	set the in_tty to achieve not_ECHO.....		*/



int getchoice(char* greet, FILE* in, FILE* out);

int char_to_terminal(int char_to_write);

int (*os)(int)=char_to_terminal;


int main(void)
{
	int choice=0;
	FILE* input;
	FILE* output;
	struct termios old,new;	//	old is default_set, new is new_set ..

	//	set the tty...
	
	int f_in=fileno(stdin);

	tcgetattr(f_in,&old);
	new=old;
	
	new.c_lflag &= ~ICANON;
	new.c_lflag &= ~ECHO;
	new.c_cc[VMIN]=1;
	new.c_cc[VTIME]=0;
	new.c_lflag &= ~ISIG;

	
	if (tcsetattr(f_in,TCSAFLUSH,&new)!=0)
	{
		fprintf(stderr,"Cannot set the IN_tty..\n");
		exit(1);
	}
	else;

	
	if (!isatty(fileno(stdout)))
		fprintf(stderr,"You are not a terminal, OK.\n");
	else;

	input=fopen("/dev/tty","r");	// ONLY_READ..
	output=fopen("/dev/tty","w");	// ONLY_WRITE..

	if (!input||!output)
	{
		fprintf(stderr,"Unable to open /dev/tty\n");
		exit(1);
	}
	else;

	do
	{
		choice=getchoice("Please select an action",input,output);
		printf("You have chosen: %c\n",choice);
	} while (choice!='q');

	if (tcsetattr(f_in,TCSAFLUSH,&old)==-1)
	{
		fprintf(stderr,"Can't reset the IN_tty..\n");
		exit(2);
	}
	else;
	
	return 0;
}

int getchoice(char* greet, FILE* in, FILE* out) // in and out are able for the /dev/tty
{
	int chosen=0;
	int selected;
	int screenrow, screencol=10;
	char** option;
	
	char *cursor, *clear;
	
	output_stream=out;
	
	//printf("NOW....\n");

	setupterm(NULL,fileno(out),NULL);
	cursor=tigetstr("cup");	// get cup_str
	clear=tigetstr("clear"); // get clear_str

	screenrow=4;
	tputs(clear,1,os); // char_to_terminal is a functional ..	(int*) is ptr...
	tputs(tparm(cursor,screenrow,screencol),1,char_to_terminal);// cursor is cup_str, screenrow and screencol is parameters
	
	fprintf(out,"Choice: %s, greet");	//	 show string

	screenrow+=2;
	option=menu;
	
	while (*option)
	{
		tputs(tparm(cursor,screenrow,screencol),1,char_to_terminal);
		fprintf(out,"%s",*option);
		screenrow++;
		option++;
	}
	
	fprintf(out,"\n");

	do
	{
		fflush(out);
		selected=fgetc(in);
		option=menu;

		while (*option)
		{
			if (selected==**option)
			{
				chosen=1;
				break;
			}
			else;
			option++;

		}
		
		if (!chosen)
		{
			tputs(tparm(cursor,screenrow,screencol),1,char_to_terminal);
			fprintf(out,"Incorrect choice, select again\n");
		}
	} while (!chosen);
	
	tputs(clear,1,char_to_terminal);
	return selected;
}

int char_to_terminal(int char_to_write)
{
	if (output_stream)
		putc(char_to_write,output_stream);
	else;
	return 0;
}
	
