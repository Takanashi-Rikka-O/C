#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
/*	Example of an argument list	*/
/*	Note that we need a program name for argv[0]	*/

char* const ps_argv[]={"ps","ax",0};

/*	Example environment, not terribly useful	*/

char* const ps_envp[]={"PATH=/bin:/usr/bin","TERM=console",0};

/*	Possible calls to exec functions	*/


/*	Example for functionals ...

execl("/bin/ps","ps","ax",0);	// assumes ps is in /bin
execlp("ps","ps","ax",0);	// assumes /bin is in PATH	This function can auto search PATH
execle("/bin/ps","ps","ax",0,ps_envp);	// passes own environment	ps_envp is environ-variable

execv("/bin/ps",ps_argv);	// ps_argv is string_array.. It's parameters .. 
execvp("ps",ps_argv);
execve("/bin/ps",ps_argv,ps_envp);

*/

int main()
{
	printf("Running ps with execlp\n");
	printf("Current_PID : %d\tParment_Process-PID: %d\n",getpid(),getppid());
	execlp("ps","ps","lax",NULL);
	printf("Done\n");
	exit(EXIT_SUCCESS);
}
