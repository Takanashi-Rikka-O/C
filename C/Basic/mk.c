#include<unistd.h>
#include<dirent.h>	//opendir; readdir; telldir; seekdir; closedir;
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
	char* path_=(char*)malloc(15*sizeof(char));	// mkdir path...
	printf("Please input mkdir path and name (15) : ");
	fgets(path_,15,stdin);
	path_[strlen(path_)-1]='\0';
	
	puts(path_);

	// ptr->DIR struct...
	DIR* tmp_=NULL;
	if ((tmp_=opendir(path_))==NULL)
	{
		fprintf(stderr,"Can't open mkdir : %s\n",path_);
		exit(1);
	}
	else printf("......\n");
	// open mkdir....

	// readdir...
	
	/*

	dirent* Next=NULL;
	if ((Next=readdir(tmp_))==NULL)
	{
		fprintf(stderr,"Readdir is NULL...\n");
		system("pause");
	}
	else printf("Readdir ... !\n");

	printf("d_ino : %d, d_name[] : %s ..\n",Next->d_ino,Next->d_name);
	// mkdir information..
	
	*/

	// telldir .. now...
	
	long now_=telldir(tmp_);
	printf("Now is : %ld \n",now_);

	
	printf("Closedir....\n");
	if (closedir(tmp_)==0)
	{
		printf("Closed..\n");
		free(path_);
	}
	else
	{
		fprintf(stderr,"Can't closed mkdir....%s\n",path_);
		exit(2);
	}
	return 0;
}
