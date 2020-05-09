#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
	char* file_name;
	
	if (argc < 2)
	{
		fprintf(stderr,"useupper file\n");
		exit(1);
	}
	else;
	file_name=argv[1];

	if (!freopen(file_name,"r",stdin))
	{
		fprintf(stderr,"could not redirect stdin from file %s\n",file_name);
		exit(2);
	}
	else;

	execl("./upper","upper",NULL);	

//	execl("./upper","upper"," < ",file_name,NULL);

	perror("could not exec ./upper\n");
	exit(3);

	//exit(EXIT_SUCCESS);
}
