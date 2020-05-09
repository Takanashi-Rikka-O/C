#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>

#include<ndbm.h>
//#include<gdbm.h>
//#include<gdbm-ndbm.h>

#include<string.h>

#define FILE_PATH "./d_test2"
#define LEN 3

struct test
{
	char str1[15];
	int value;
	char str2[21];
};


int main(void)
{
	struct test ONE[LEN];
	struct test TWO;
	
	//	data


	char key[20];	//	search string

	datum key_datum;	//	search
	datum data_datum;	//	data

	DBM* dbm_ptr;	//	dbm' ptr
	
	int i, result;


	dbm_ptr=dbm_open(FILE_PATH,O_RDWR | O_CREAT,0666);	//	open dbm
	if (dbm_ptr == NULL)
	{
		fprintf(stderr,"Failed to open database\n");
		exit(2);
	}
	else;

	memset(ONE,'\0',sizeof(ONE));

//	---------------------------

	strcpy(ONE[0].str1,"First");
	ONE[0].value=22;
	strcpy(ONE[0].str2,"foo");

	strcpy(ONE[1].str1,"bar");
	ONE[1].value=31;
	strcpy(ONE[1].str2,"unlucky?");

	strcpy(ONE[2].str1,"Third");
	ONE[2].value=24;
	strcpy(ONE[2].str2,"baz");
	
//	---------------------------

	
	for (i=0; i < LEN; ++i)
	{
		sprintf(key,"%c%c%d",ONE[i].str1[0],ONE[i].str2[0],ONE[i].value);

		key_datum.dptr=(void*)key;
		key_datum.dsize=strlen(key);
		data_datum.dptr=(void*)&ONE[i];
		data_datum.dsize=sizeof(struct test);

		result=dbm_store(dbm_ptr,key_datum,data_datum,DBM_REPLACE);
		if (result)
		{
			fprintf(stderr,"dbm_store failed on key %s\n",key);
			exit(3);
		}
		else;
	}

	sprintf(key,"Ff%d",ONE[0].value);


	if (dbm_delete(dbm_ptr,key_datum) == 0)
		printf("Data with key %s deleted\n",key);
	else
		printf("Nothing deleted for key %s\n",key);

	//	---------------------------	delete data
	
	





	for (key_datum=dbm_firstkey(dbm_ptr); key_datum.dptr; key_datum=dbm_nextkey(dbm_ptr))
	{




	data_datum=dbm_fetch(dbm_ptr,key_datum);	//	get data

	if (data_datum.dptr)
	{
		printf("Data retrieved\n");
		memcpy(&TWO,data_datum.dptr,data_datum.dsize);
		printf("TWO - item - %s %d %s\n",TWO.str1,TWO.value,TWO.str2);
	}
	else
		printf("Not have this string %s --- data\n",key);

	}


	dbm_close(dbm_ptr);	//	shutdown the gdbm

	


	exit(EXIT_SUCCESS);
}

