#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	char file[L_tmpnam];// temp_file memory
	char* tmpname=NULL;// tmpname can return a char* ...	
	FILE* temp;// tmpfile return ..
	
	printf("Open temp_file ... \n");
	tmpname=tmpnam(file);
	printf("address:\nfile_: %p\ttmpname_: %p\nfile_name: %s\ntmpname_name: %s\n",
			file,tmpname,file,tmpname);
	
	printf("\nWe use the tmpfile()....\n");
	temp=tmpfile();
	if (temp==NULL)
		printf("tmpfile is error, temp==NULL\n");
	else
		printf("tmpfile_return--temp : %s\n %p\n",temp,temp);

	return 0;
}
