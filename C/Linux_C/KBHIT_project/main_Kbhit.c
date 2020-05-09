#include<stdio.h>
#include"Kbhit.h"

int main(void)
{
	int ch=0;

	init_keyboard();		//	New setting and save default setting.
	
	while (ch!='q')			//	There usage polling method for get a character,this is a very low effectiveness method.
	{
		printf("looping\t.\n");
		sleep(1);
		if (kbhit())	//kbhit() haven't input, return 0
		{
			ch=readch();
			printf("You hit %c\n",ch);
		}
		else;
	}
	close_keyboard();

	return 0;
}
