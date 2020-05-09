#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void printfdir(char* dir, int depth);

int main(void)
{
	printf("Directory scan of /root: \n");
	printfdir("/root/Storage/Projects",0);
	printf("done...\n");

	return 0;
}

void printfdir(char* dir, int depth)
{
	DIR* dp;
	struct dirent* entry;
	struct stat statbuf;

	if ((dp=opendir(dir))==NULL)
	{
		fprintf(stderr,"Cannot open directory: %s\n",dir);
		exit(1);
	}
	else;
	
	chdir(dir);

	while ((entry=readdir(dp))!=NULL)
	{
		lstat(entry->d_name,&statbuf);
		if (S_ISDIR(statbuf.st_mode))
		{
			if (strcmp(".",entry->d_name)==0||strcmp("..",entry->d_name)==0)
					continue;
			else
					printf("%*s%s/\n",depth," ",entry->d_name);

			printfdir(entry->d_name,depth+4);
		}
		else printf("%*s%s\n",depth," ",entry->d_name);
	}
	
	chdir("..");
	closedir(dp);
}
