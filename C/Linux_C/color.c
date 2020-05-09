#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<curses.h>

int main(void)
{

	int i;


	initscr();

	if (!has_colors())
	{
		endwin();
		fprintf(stderr,"Error - no color support on this terminal\n"); // this tty can't use colors
		exit(1);
	}
	else;

	if (start_color() != OK)
	{
		endwin();
		fprintf(stderr,"Error - could not initalize colors\n");
		exit(2);
	}
	else;

	clear();

	mvprintw(5,5,"There are %d COLORS, and %d COLOR_PAIRS available",COLORS,COLOR_PAIRS);

	refresh();

	init_pair(1,COLOR_RED,COLOR_BLACK);	// set the colors_pair... 1-> ID, 2-> foreground, 3-> background ..
	init_pair(2,COLOR_RED,COLOR_GREEN);
	init_pair(3,COLOR_GREEN,COLOR_RED);
	init_pair(4,COLOR_YELLOW,COLOR_BLUE);
	init_pair(5,COLOR_BLACK,COLOR_WHITE);
	init_pair(6,COLOR_MAGENTA,COLOR_BLUE);
	init_pair(7,COLOR_CYAN,COLOR_WHITE);

	//	colors -- == 8,  color_pairs -- == 64... ( 0----63 )
	

	for (i=1; i <= 7; ++i)
	{
		attroff(A_BOLD); // off A_BOLD..
		attrset(COLOR_PAIR(i)); // set color_(i) -> init_pair()...

		mvprintw(5+i,5,"Color pair %d",i);
		attrset(COLOR_PAIR(i) | A_BOLD); // set color_(i) and A_BOLD .. open |

		mvprintw(5+i,25,"Bold color pair %d",i);

		refresh();
		sleep(2);

	}
	

	getchar();

	endwin();	

	exit(EXIT_SUCCESS);
}
