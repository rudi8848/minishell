/*
#include "minishell.h"
#include <errno.h>
#include <stdio.h>
int		main(void)
{
	pid_t pid;

	pid = fork();

		//perror("fork");
	if (pid == -1)
	{

		exit (0);
	}
	if (pid == 0)
	{
		int ret;
		printf("--->child\n");
		char *argv[] = {"/bin/ls", "-l", NULL};
		ret = execve("/bin/ls", argv, NULL);
			//perror("execve");
		exit (0);
	}
	else
	{
		printf("--->parent\n");
		int status;

		pid = wait(&status);
			//perror("wait");
	}

	return 0;
}
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

pid_t pid;

int main(void)
{
	printf("\nfork(), exit(), getpid(), getppid(), wait() example\n\n");
	
	printf("\\/ step 1 (potential PARENT): forking ... ");
	fflush(stdout);
 
//Without flushing CHILD also outputs the string above!!!
//Of course, flushing can be done by outputting "\n".

	
	pid = fork();
	
	if ( pid == -1 ) {
		printf("fork()'ing FAILED\n");
		exit(0);
	};
	
	if ( pid == 0 ) { // we are CHILD process
	
		pid_t my_pid = getpid();
		pid_t pa_pid = getppid();
		
		printf("\\/ step 1 (CHILD): Hello, world! \
			I am child process.\n");
		printf("\\/ step 2 (CHILD): I am %d and my \
			parent is %d.\n", my_pid, pa_pid);


		char * program = "/bin/ls";
		char * argv[] = {"/bin/ls","-l", NULL};
		char * envp[] = {NULL};
		printf("(CHILD) is going to execve %s\n", program);
		int ret;
		ret = execve(program, argv, envp);
		if ( ret == -1 ) {
			perror("--CHILD-- execve()");
			exit(1);
		};
			
		printf("\\/ step 3 (CHILD): exiting ...\n");
		sleep(5); // let the parent wait a little bit
		exit(123);
		
	} else {          // we are PARENT process

		pid_t my_pid = getpid();
		pid_t pa_pid = getppid();
		pid_t fork_pid = pid;
		int child_status;
		
		printf("(PARENT) fork()'ing OK\n");
		
		printf("\\/ step 2 (PARENT): Hello, world! I am parent process.\n");
		printf("\\/ step 3 (PARENT): I am %d, my parent is %d and my child is %d.\n", my_pid, pa_pid, fork_pid);
		printf("\\/ step 4 (PARENT): waiting for child complition ...\n");
		
		pid = wait(&child_status);
		if ( pid == -1 ) {
			printf("(PARENT): ooopssss ... wait()'ing FAILED.\n");
		} else {
			printf("(PARENT): wait()'ing OK, child %d exited, exit code is %d.\n", 
			pid, WEXITSTATUS(child_status));
		};
		
		printf("\\/ step 5 (PARENT): exiting ...\n");
		exit(0);
	};
}

