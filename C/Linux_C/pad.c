#include<unistd.h>
#include<stdlib.h>
#include<curses.h>

int main(void)
{

	WINDOW* pad_ptr;

	int x,y;
	int pad_lines;
	int pad_cols;
	char disp_char='a';

	initscr();

	pad_lines=LINES+50;
	pad_cols=COLS+50;

	pad_ptr=newpad(pad_lines,pad_cols); // create a pad_struct....

	for (x=0; x < pad_lines; ++x)
	{
		for (y=0; y < pad_cols; ++y)
		{
			mvwaddch(pad_ptr,x,y,disp_char);
			
			if (disp_char=='z')	disp_char='a';
			else disp_char++;		
		}
	}
	
	sleep(1);

	prefresh(pad_ptr,5,7,2,2,9,9);	
	//	pad_ptr->screen_ptr
	//	5,7 -> pad's coordinate...
	//	2,2 -> stdscr's coordinate...
	//	9,9 -> stdscr's coordinate...
	//
	//	2,2 ---- 9,9 -> range
	sleep(3);
	
	move(15,15);
	printw("--> 5,5  12,13");
	refresh();


	prefresh(pad_ptr,8,21,5,5,12,13);
	sleep(3);

	delwin(pad_ptr);	// delete pad_screen .. 



	endwin();

	sleep(5);	

	exit(EXIT_SUCCESS);
}
