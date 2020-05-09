#include<unistd.h>
#include<curses.h>
//#include<stdio.h>


int main(void)
{
//	printf("Set screen\n");

	initscr();

	// standout(); backgound : white...
	
	standend(); // in shell not have variety

	move(13,10);	// move cursor to 5_line 15_colr ..
	printw("%s","Hello World");	// flush logic_screen .. -> tty_screen..
    
	refresh();	// flush physical_screen .. -> stdscr : std_screen..	show information in the screen
    
	//system("pause");
	
//	printf("Overn\n");

	//system("pause");

	//clear();

	move(8,10);
	refresh();
	
	beep();
	flash();
	
	sleep(5);
//	clear();


	endwin();
	
	return 0;
}
