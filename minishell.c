#include "minishell.h"
#include "get_next_line.h"
#include <stdio.h>

#define CLEAR "\e[1;1H\e[2J"
#define RESET "\033[0m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"

void	type_prompt(char **envp)
{
	char	*user;
	char	*pwd;
	char	*home;
	int	len;

	user = get_env("LOGNAME", envp);
	pwd = get_env("PWD", envp);
	home = get_env("HOME", envp);
	len = ft_strlen(home);
	if (ft_strnequ(home, pwd, len))
	{
		home = "~";
		pwd = ft_strsub(pwd, len, ft_strlen(pwd) - len);
	}
	else
		home = "";
		ft_printf("%s%s: %s%s%s>%s ", RED,user,GREEN, home, pwd, RESET);

}

int	check_built(char *cmd)
{/*
	int i = 0;
	t_pfb	f_built;
	t_prb arr_built[BUILT] = {ft_cd};
	char **built = {"cd", NULL};
	while (built[i] != NULL)
	{
		if (ft_strequ(cmd, built[i]))
		{
			f_built = &arr_built[i];
			f_built(cmd, envp);
			return (i);
		}
		i++;
	}*/
	return (0);
}
void ft_built_exe(char **args, char **envp)
{
	;
}

void ft_cmd_exe(char **args, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		ft_printf("Error");
		exit(0);
	}
	else if (pid == 0)
	{
		status = execve(args[0], args, envp);
		if (args[0] && status < 0)
			ft_printf("%s: command not found", args[0]);
		exit (0);
	}
	else
		wait(&status);
}

void	executor(t_cmd_list *commands, char **envp)
{
	int ret;
	while (commands)
	{
	ret = check_built(commands->args[0]);
	if (ret)
		ft_built_exe(commands->args, envp);
	else
	{
		ret = ft_find(commands, envp);
		if (ret)
			ft_cmd_exe(commands->args, envp);
	}
	commands = commands->next;
}
}


int	main(int argc, char *argv[], char *envp[])
{
	char *line;
	int ret = 1;
	t_cmd_list *commands;

	ft_printf("%s", CLEAR);

	while (ret > 0)
	{
		type_prompt(envp);
		//write(1, "###> ", 5);
		ret = get_next_line(1, &line);
		commands = parser(line);
		free(line);
	if (commands)
		executor(commands, envp);
	ft_printf("\n");
}
	return (0);
}
