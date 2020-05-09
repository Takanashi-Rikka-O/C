#include<unistd.h>
#include<sys/types.h>
#include<pwd.h>
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	uid_t uid;
	gid_t gid;

	struct passwd* temp_ps;

	puts("Get uid and gid...");
	uid=getuid();
	gid=getgid();

	printf("User is %s\n",getlogin());
	
	printf("User ID uid=%d\tgid=%d\n",uid,gid);

	puts("Use of getpwuid()...\n");
	
	temp_ps=getpwuid(uid);// return a password_struct...

	puts("Show all information ... ");

	printf("login_name: %s\nUID: %d\nGID: %d\n~: %s\nUser_name: %s\nSHELL: %s\n",
		temp_ps->pw_name,temp_ps->pw_uid,temp_ps->pw_gid,temp_ps->pw_dir,
		temp_ps->pw_gecos,temp_ps->pw_shell);



	return 0;
}
