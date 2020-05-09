#ifndef _KBHIT_H
#define _KBHIT_H

#include<stdlib.h>
#include<termios.h>
#include<term.h>
#include<curses.h>
#include<unistd.h>

void init_keyboard();
void close_keyboard();
int kbhit();
int readch();

#endif
