#include<unistd.h>
#include<stdlib.h>
#include<curses.h>
#include<string.h>

#define PW_LEN 256
#define NAME_LEN 256


int main()
{
	char name[NAME_LEN];
	char password[PW_LEN];
	const char* real_password="xyzzy";
	
	int i=0;
	
	initscr();
	
	move(5,10);
	printw("%s","Please login : ");
	
	move(7,10);
	printw("%s","User name : ");
	getstr(name);	// in the ncurses, getstr can auto use the refresh() ;
	
	move(8,10);
	printw("%s","Password : ");
	
	refresh();
	
	
	cbreak();	// not buffer...  cookeb-mode is line_buffer..
	noecho();	// not show input...
	
	memset(password,'\0',sizeof(password));	// memset() can initializal memory to one 'char' .. 
	// 1 -> address ;	2 -> char value ;	3 -> the memory's long ;
	
	while (i<PW_LEN)
	{
		password[i]=getch();	// getch() return the input...  int value...
		
		if (password[i] == '\n')
		{
			password[i]='\0';
			break;
		}
		else;
		
		move(8,20+i++);
		addch('*');
		refresh();
	}
	
	echo();	// open show input
	
	nocbreak(); // reset input-mode to cooked-mode..
	
	move(11,10);
	
	if (strncmp(real_password,password,sizeof(real_password))==0)
		printw("%s","Correct");
	else
		printw("%s","Wrong");
	
	refresh();
	
	sleep(5);
	
	endwin();
	
	
	
	exit(EXIT_SUCCESS);
}
