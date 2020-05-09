#include<stdio.h>
#include<stdlib.h>

// #include<conio.h>  Linux is not have conio.h ...

#include<unistd.h>


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


int getchoice(char* greet, FILE* in, FILE* out);

int main(void)
{
	int choice=0;
	FILE* input;
	FILE* output;

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
		} while (selected=='\n');
		
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
	} while (!chosen);

	return selected;
}
	
