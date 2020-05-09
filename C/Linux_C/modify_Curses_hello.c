#include<unistd.h>
#include<curses.h>


int main(void)
{
/*
	initscr();
	move(5,15);	// move cursor to 5_line 15_colr ..
	printw("%s","Hello World");	// flush logic_screen .. -> tty_screen..
    
	refresh();	// flush physical_screen .. -> stdscr : std_screen..	show information in the screen
	endwin();

*/

// two
//

	initscr();
	move(5,5);
	printw("%s\n","Hellow World");
	endwin();

	clearok(stdscr,1);
	refresh();


	return 0;
}
