#include<unistd.h>
#include<stdlib.h>
#include<curses.h>
#include<stdbool.h>


int main(void)
{
	WINDOW* sub_window_ptr;
	int x_loop,y_loop;
	int counter;
	char a_letter='a';
	
	initscr();
	
	sleep(2);
	
	for (y_loop=0; y_loop < LINES-1; ++y_loop)
	{
		for (x_loop=0; x_loop < COLS-1; ++x_loop)
		{
			mvwaddch(stdscr,y_loop,x_loop,a_letter);
			
			a_letter=(++a_letter > '9')?'1':a_letter;
		}	
	}
	
	// generate scroll_sub_window....
	
	sub_window_ptr=subwin(stdscr,10,20,10,10);	// lines=10, cols=20, y=10, x=10
	scrollok(sub_window_ptr,true);	// Can Scroll (true) , Can't Scroll (false)
	
	touchwin(stdscr);	// Parent_window have to touchwin() must in sub_window's update before...
	refresh();	// update parent_window -> stdscr..
	sleep(3);
	
	// -----------------------
	
	werase(sub_window_ptr); // delete char_value in the sub_window_ptr... Set to ' ' ....
	mvwprintw(sub_window_ptr,2,0,"%s","This window will now scroll"); // write int sub_window
	wrefresh(sub_window_ptr);	// update sub_window
	sleep(2);
	
	for (counter=1; counter < 10; ++counter)
	{
		wprintw(sub_window_ptr,"%s","This text is both wrapping and scrolling");
		wrefresh(sub_window_ptr);
		sleep(1);
	}
	
	// --------   delete sub_window
	
	delwin(sub_window_ptr);
	
	touchwin(stdscr);
	refresh();
	sleep(3);
	
	
	endwin();
	
	exit(EXIT_SUCCESS);
}
