#include"Kbhit.h"

static struct termios initial,new;
static int peek_character=-1;	// if have a char in stdin.. change the peek_character..

void init_keyboard()	//	set stdin..
{
	tcgetattr(0,&initial);
	new=initial;

	new.c_lflag &= ~ICANON;	// Close Standard-mode
	new.c_lflag &= ~ECHO;	// Close ECHO
	new.c_lflag &= ~ISIG;	// Close SIGNAL
	new.c_cc[VMIN]=1;	// set MIN=1	Input min limit.
	new.c_cc[VTIME]=0;	// set TIME=0	Input min time limit.

	tcsetattr(0,TCSANOW,&new); // set stdin...	Set up this attrbute.
}

void close_keyboard()	//	reset stdin
{
	tcsetattr(0,TCSANOW,&initial);		//	Return to default.
}

int kbhit()	// Features ... keyboard hit..
{
	char ch;
	int re_read;	//	re_read is read() 's return ..

	if (peek_character!=-1)	//	peek_character is not -1, stdin have input..
		return 1;	//	keyhit() is true return 1, otherwise return 0 is false..
	else;
	
	new.c_cc[VMIN]=0;		// Not_Standard-mode .. MIN(0),TIME(0) read() straightway return .. 
	tcsetattr(0,TCSANOW,&new);	//	set standard input..

	re_read=read(0,&ch,1);		//	Now,read will not wait for time,if not have input from stdin during 1s,read will return straight.
	// read() have input,return input_numbers.
	// otherwise return 0

	if (1 == re_read)		// set read() read a char.. re_read==1, have input
	{
		peek_character=ch; 	// Assignment pee_character=ch.The 'ch' is a input at just now.
		return 1;		// return 1 , have hit
	}
	else
		return 0;
}

int readch()
{
	char ch;
	
	if (peek_character!=-1)	// peek_character != -1, have hit
	{
		ch=peek_character;	// set ch to peek_character..
		peek_character=-1;	// reset peek_character = -1..
		return ch;	// return ch
	}
	else
		read(0,&ch,1);	// otherwise use the read() get a char..
	return ch;	//	return ch
}
