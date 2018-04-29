#include "minishell.h"
#include "get_next_line.h"
#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	char *line;
	int ret = 1;
	char **command;
	pid_t pid;
	int status = 1;

	while (ret > 0)
	{
		write(1, "###> ", 5);
		ret = get_next_line(1, &line);
	if (ret > 0)	
		command = parser(line, envp);
		
		free(line);
		pid = fork();
		
		if (pid < 0)
		{
			perror("fork");
			exit(0);
		}
		
		else if (pid == 0)
		{
			printf("CHILD: %d\n", getpid());
			status = execve(command[0], command, NULL);
			if (command[0] && status < 0)
				printf("%s: command not found\n", command[0]);
			perror("execve");
			exit(0);
		}
		else
		{
			printf("PARENT: %d\n", getpid());
			wait(&status);
		}
	}
	return (0);
}
