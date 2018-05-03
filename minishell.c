#include "minishell.h"
#include "get_next_line.h"
#include <stdio.h>



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
{
	int i = 0;
	char *built[] = {"echo", "cd", "setenv", "unsetenv", "env", "exit", NULL};
	while (built[i])
	{
		if (ft_strequ(cmd, built[i]))
			return (i);
		i++;
	}
	return (-1);
}

void	ft_set_builtins(t_pfb *built_tab)
{
	built_tab[ECHO] = &ft_echo;
	built_tab[CD] = &ft_cd;
	built_tab[SETENV] = &ft_setenv;
	built_tab[UNSETENV] = &ft_unsetenv;
	built_tab[ENV] = &ft_env;
	built_tab[EXIT] = &ft_exit;
}

void ft_built_exe(char **args, char **envp, t_built cmd)
{
	static t_pfb	*built_tab = NULL;
	t_pfb			ft_run;
	if (!built_tab)
	{
		built_tab = (t_pfb*)ft_memalloc(sizeof(t_pfb) * BUILT);
		if (!built_tab)
		{
			ft_printf("Error\n");
			return;
		}
		ft_set_builtins(built_tab);
	}
	ft_run = built_tab[cmd];
	ft_run(args, envp);
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
	if (ret >= 0)
		ft_built_exe(commands->args, envp, ret);
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

	while (1)
	{
		type_prompt(envp);
		//write(1, "###> ", 5);
		ret = get_next_line(1, &line);
		commands = parser(line);
		free(line);
	if (commands)
		executor(commands, envp);
	if (!ret)
		ft_printf("\n");
}
	return (0);
}
