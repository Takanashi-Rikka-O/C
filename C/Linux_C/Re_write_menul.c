#include<stdio.h>
#include<stdlib.h>

// #include<conio.h>  Linux is not have conio.h ...

#include<unistd.h>
#include<termios.h>

char* menu[]={
	"a - add new record",
	"d - delete record",
	"q - quit",
	NULL};




/*    ------- 1 -------

int getchoice(char* greet);

int main(void)
{
	int choice=0;

	do
	{
		choice=getchoice("Please select an action");
		printf("You have chosen: %c\n",choice);

	} while (choice!='q');
	return 0;
}

int getchoice(char* greet)
{
	int chosen=0;
	int selected;
	char** option;

	do
	{
		printf("Choice: %s\n",greet);
		option=menu;
		while (*option)
			puts(*option++);
		
		//selected=getch();	// not have conio.h
		
		selected=getchar();
		getchar();// throw away the '\r' ...

		option=menu;
		
		while (*option)
		{
			if (selected==**option++)
			{
				chosen=1;
				break;
			}
			else;
		}
		
		if (!chosen)
			puts("Incorrect choice, select again");
		else;
	} while (!chosen);

	return selected;

}
      ------- 1 -------  */



//    ------- 2 -------

//	/dev/tty is link the Current Sesion ... (Use the tty now ... Command_Prompt ) 




/*	set the in_tty to achieve not_ECHO.....		*/



int getchoice(char* greet, FILE* in, FILE* out);

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
	char** option;

	do
	{
		fprintf(out,"Choice: %s\n",greet);
		option=menu; // menu have external link ... It's a char_string_array ..
		while (*option)
			fprintf(out,"%s\n",*option++);
		do
		{
			selected=fgetc(in);
		} while (selected=='\n'||selected=='\r');
		
		option=menu;

		while (*option)
			if (selected==**option++)
			{
				chosen=1;
				break;
			}
			else;

		if (!chosen)
			fprintf(out,"Incorrect choice, select again\n");
		else;
	} while (!chosen);

	return selected;
}
	
