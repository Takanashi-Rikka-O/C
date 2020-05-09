#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	int pt[]={1,2,3,4,5,6,7,8};
	int x=0;
	int* fs=pt;
	*(fs+9)=11;
	char pl[]={"ABCDEFG"};
	char* kksk=pl;
	while (*kksk)
	{
		printf("now is %c\n",*kksk++),++x;
	}
	printf("char_x is %d \n",x);

	
	char* pas[]={"OPP","OCC","LKS"};

	x=0;

	char** ppp=pas;

	while (*ppp)
	{
		printf("str is : %s\n",*ppp++),++x;
	}

	printf("ppp+3 is %p \n",ppp+3);
	printf("\t ppp+3 is d_ %d\n",*(ppp+3));

	printf("str[]_x is %d\n",x);



	x=0;
	while (*fs)
	{
		if (12==++x)
			{
				printf("x is : %d\n",x);
				exit(1);
			}
		else printf("\tx is %d\n",x);
		printf("--%d\n",*fs++);
	}
	printf("while---- x is : %d\t *fs is : %d \n",x,*fs);



	return 0;
}
