#include "minishell.h"
#include "get_next_line.h"
#include <stdio.h>

#define CLEAR "\e[1;1H\e[2J"

int	main(int argc, char *argv[], char *envp[])
{
	char *user;
	char *curdir;
	char *line;
	int ret = 1;
	char **command;
	pid_t pid;
	int status = 1;
ft_printf("%s", CLEAR);

	user = get_env("USERNAME", envp);
	curdir = get_env("PWD", envp);
	while (ret > 0)
	{
		ft_printf("[%s][%s]> ", user, curdir);
		//write(1, "###> ", 5);
		ret = get_next_line(1, &line);
		command = parser(line, envp);
	printf("---> %s\n", __FUNCTION__);	
		free(line);
		
		if (command)
		{
		pid = fork();
		
		if (pid < 0)
		{
			perror("fork");
			exit(0);
		}
		
		else if (pid == 0)
		{
//			printf("CHILD: %d\n", getpid());
			status = execve(command[0], command, NULL);
			if (command[0] && status < 0)
				printf("%s: command not found\n", command[0]);
			perror("execve");
			exit(0);
		}
		else
		{
//			printf("PARENT: %d\n", getpid());
			wait(&status);
		}
		}
	}
	return (0);
}
