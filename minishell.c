#include "minishell.h"
#include <stdio.h>



void	type_prompt(char **envp)
{
	printf("---> %s\n", __FUNCTION__);
	char	*user;
	char	*pwd;
	char	*home;
	int	len;
	char	*tmp;

	user = get_copy_env("LOGNAME", envp);
	pwd = get_current_wd();
	home = get_copy_env("HOME", envp);
	len = ft_strlen(home);
	if (ft_strnequ(home, pwd, len))
	{
//		free(home);
		home = "~";
		tmp = ft_strsub(pwd, len, ft_strlen(pwd) - len);
	}
	else
	{
//		free(home);
		home = "";
		tmp = pwd;
	}
		ft_printf("%s%s: %s%s%s>%s ", RED,user, GREEN, home, tmp, RESET);
		//ft_strdel(&pwd);
		if (tmp != pwd)
			ft_strdel(&tmp);
		
//		ft_strdel(&user);
}

int	check_built(char *cmd)
{
	printf("---> %s\n", __FUNCTION__);
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
	ft_run(args, &envp);
}

void ft_cmd_exe(char **args, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		ft_printf("Error\n");
		exit(0);
	}
	else if (pid == 0)
	{
		status = execve(args[0], args, envp);
		if (args[0] && status < 0)
			ft_printf("%s: command not found\n", args[0]);
		exit (0);
	}
	else
		wait(&status);
}

void	ft_list_del(t_cmd_list **commands)
{
	printf("---> %s\n", __FUNCTION__);
	t_cmd_list *prev;

	while (*commands)
	{
		prev = (*commands);
		(*commands) = (*commands)->next;
		free_arr(prev->args);
		//ft_strdel(prev->args);
		free(prev);
	}
	//free(*commands);
}

void	executor(t_cmd_list *commands, char **envp)
{
	printf("---> %s\n", __FUNCTION__);
	int ret;
	t_cmd_list *tmp;

	tmp = commands;
	while (commands)
	{
		//--------------------
		int i = 0;
		while (commands->args[i])
		{
			printf("--> [	%s	]\n", commands->args[i]);
			i++;
		}
		//-------------------
		ret = check_built(commands->args[0]);
		if (ret >= 0)
			ft_built_exe(commands->args, envp, ret);
		else
		{
			ret = ft_find(commands, envp);
	printf("---> %s\n", __FUNCTION__);
			if (ret)
				ft_cmd_exe(commands->args, envp);
		}
		commands = commands->next;
	}
	ft_list_del(&tmp);
}

char	**copy_env(void)
{
	printf(">>>>>>>>> %s <<<<<<<<<<\n", __FUNCTION__);
	extern char **environ;
	int size;
	char	**copy;
	int	i;

	i = 0;
	size = env_size(environ);
	if (!size)
	{
		ft_printf("Error: cannot allocate memory\n");
		exit(0);
	}
	copy = (char**)ft_memalloc(sizeof(char*) * size + 1);
	if (!copy)
		exit(0);
	while (environ[i])
	{
		copy[i] = ft_strdup(environ[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	main(void)
{
	char *line;
	int ret = 1;
	t_cmd_list *commands;
	char **envp;

	ft_printf("%s", CLEAR);
	envp = copy_env();
	
	while (1)
	{
		type_prompt(envp);
		ret = get_next_line(1, &line);
		commands = parser(line);
		free(line);
	if (commands)
		executor(commands, envp);
	if (!ret)
		ft_printf("\n");
}
system("leaks minishell");
	return (0);
}
