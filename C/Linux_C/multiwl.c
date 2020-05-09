#include<unistd.h>
#include<stdlib.h>
#include<curses.h>

int main(void)
{
	WINDOW* new_window_ptr;
	WINDOW* popup_window_ptr;
	// declare two WINDOW_ptr ..
	
	int x_loop,y_loop;	// x,y coordinate ...
	
	char a_letter='a';	// char value 
	
	initscr();	// initializal stdscr
	
	move(5,5);
	printw("%s","Testing multiple windows");
	refresh();	// update for stdscr
	
	for (y_loop=0; y_loop < LINES - 1; ++y_loop)
	{
		for (x_loop=0; x_loop < COLS-1; ++x_loop)
		{
			mvwaddch(stdscr,y_loop,x_loop,a_letter++);
			if (a_letter > 'z') a_letter='a';
			else;
		}
	}
	
	refresh();	// update stdscr
	sleep(3);
	
	
	// new_window...
	
	new_window_ptr=newwin(10,20,5,5);	// lines=10, cols=20, y=5, x=5 
	mvwprintw(new_window_ptr,2,2,"%s","Hello World");
	mvwprintw(new_window_ptr,5,2,"%s","Notice how very long lines wrap inside the window");
	wrefresh(new_window_ptr);	// update the new_window
	sleep(3);
	
	
	a_letter='0';
	
	for (y_loop=0; y_loop < LINES-1; ++y_loop)
	{
		for (x_loop=0; x_loop < COLS-1; ++x_loop)
		{
			mvwaddch(stdscr,y_loop,x_loop,a_letter);
			if (++a_letter > '9')
				a_letter='0';
			else;
		}
	}
	refresh();	// regenerate stdscr .. update
	sleep(3);
	
	
	wrefresh(new_window_ptr);	// flush the new_window.. but not update information.. It's not changed...
	sleep(3);
	
	
	
	touchwin(new_window_ptr);	// Notice window_information is changed to <curses> ..
	wrefresh(new_window_ptr);	// flush new_window..
	sleep(3);
	
	popup_window_ptr=newwin(10,20,8,8);	// generate new_window.. LINES=10, COLS=20, y=8, x=8
	box(popup_window_ptr,'|','-');	// vertical -> chuizhi.... horizontal -> shuiping....
	//	WINDOW*, char_ver, char_hori
	mvwprintw(popup_window_ptr,5,2,"%s","Pop Up Window!"); // y=5, x=2..
	wrefresh(popup_window_ptr);
	sleep(3);
	
	
	
	// ---------------------------
	
	
	// one -> show new_window_ptr->window..
	
	touchwin(new_window_ptr);
	wrefresh(new_window_ptr);
	sleep(3);
	wclear(new_window_ptr);
	wrefresh(new_window_ptr);
	sleep(3);
	delwin(new_window_ptr);	// delete window .. new_window_ptr
	
	
	// second -> show popup_window_ptr->window
	
	touchwin(popup_window_ptr);
	wrefresh(popup_window_ptr);
	sleep(3);
	delwin(popup_window_ptr); // delete window .. popup_window_ptr
	
	
	// third -> show stdscr...
	
	touchwin(stdscr);
	refresh();
	sleep(3);
	
	// !!!!! Cannot to delete for < stdscr > and < curscr > ...!!!!
	
	
	
	
	
	endwin();	// reset stdscr..
	
	exit(EXIT_SUCCESS);
}