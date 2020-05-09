#include<unistd.h>
#include<stdio.h>
#include<time.h>

int main(void)
{
	time_t The_time=0;
	
	struct tm* pt;
	struct tm* local_pt;
	char* tmp_time;

	for (int x=1; x<10; ++x)
	{
		The_time=time((time_t*)0);
		
		pt=gmtime(&The_time);	
		local_pt=localtime(&The_time);
		printf("The_time is : %ld\n\n",The_time);
		printf("GMT_TIME: \t");
		printf("%d/%d/%d/%d/%d/%d  ---\n",
				pt->tm_year+1900,pt->tm_mon+1,pt->tm_mday,pt->tm_hour,pt->tm_min,pt->tm_sec);

		//time_year is 1900 start...    January starting is 0...  hour is .U.S ( United States)

		printf("LOCAL_TIME: \t");
		printf("%d/%d/%d/%d/%d/%d  ---\n\n",
				local_pt->tm_year+1900,local_pt->tm_mon+1,local_pt->tm_mday,
				local_pt->tm_hour,local_pt->tm_min,local_pt->tm_sec);


		//asctime and ctime...   they return a string-time...
		//return string have \n.....

		puts("\n****************\n");

		tmp_time=asctime(pt);
		printf("pt_asctime : %s",tmp_time);
		printf("local_pt_asctime : %s",asctime(local_pt));
		tmp_time=ctime(&The_time);
		printf("ctime : %s",tmp_time);

		puts("\n****************\n");

		

		sleep(2);
	}

	double tmp_times=0;

	tmp_times=difftime(time(0),time(0));

	printf("difftime re is %f\n",tmp_times);


	return 0;
}	
