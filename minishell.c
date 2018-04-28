#include "minishell.h"
#include "get_next_line.h"
#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	char *line;
	int ret = 1;
	char **arr;
	pid_t pid;
	int status = 1;
	//printf("###>");
	while (ret > 0)
	{
		write(1, "###> ", 5);
		ret = get_next_line(1, &line);
		arr = ft_strsplit(line, ' ');
	
		if (!arr)
			exit(0);
		/*
		int i = 0;
		while (arr[i] != NULL)
		{
			printf(">%s\n", *arr);
			i++;
		}*/
		free(line);
		pid = fork();
		
		if (pid < 0)
		{
			perror("fork");
			exit(0);
		}
		
		else if (pid == 0)
		{
			//printf("CHILD: %d\n", getpid());
			status = execve(arr[0], arr, NULL);
			if (arr[0] && status < 0)
				printf("%s: command not found\n", arr[0]);
			//perror("execve");
			exit(0);
		}
		else
		{
			//printf("PARENT: %d\n", getpid());
			wait(&status);
		}
	}
	return (0);
}
