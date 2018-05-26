/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 15:05:25 by gvynogra          #+#    #+#             */
/*   Updated: 2018/05/12 15:05:28 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_built(char *cmd)
{
	int		i;
	char	*built[BUILT];

	i = 0;
	built[ECHO] = "echo";
	built[CD] = "cd";
	built[SETENV] = "setenv";
	built[UNSETENV] = "unsetenv";
	built[ENV] = "env";
	built[EXIT] = "exit";
	built[END] = NULL;
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
	built_tab[END] = NULL;
}

void	ft_built_exe(char **args, char ***g_envp, t_built cmd)
{
	static t_pfb	*built_tab = NULL;
	t_pfb			ft_run;

	if (!built_tab)
	{
		built_tab = (t_pfb*)ft_memalloc(sizeof(t_pfb) * BUILT);
		if (!built_tab)
		{
			ft_printf("Error\n");
			return ;
		}
		ft_set_builtins(built_tab);
	}
	ft_run = built_tab[cmd];
	ft_run(args, g_envp);
}

void	ft_cmd_exe(char **args, char **g_envp)
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
		signal(SIGINT, SIG_DFL);
		status = execve(args[0], args, g_envp);
		if (args[0] && status < 0)
			ft_printf("%s: command not found\n", args[0]);
		exit(0);
	}
	else
		wait(&status);
}

void	executor(t_cmd_list *commands, char ***g_envp)
{
	int			ret;
	t_cmd_list	*tmp;

	tmp = commands;
	while (commands)
	{
		ret = check_built(commands->args[0]);
		if (ret >= 0)
			ft_built_exe(commands->args, g_envp, ret);
		else
		{
			ret = ft_find(commands, *g_envp);
			if (ret)
				ft_cmd_exe(commands->args, *g_envp);
		}
		commands = commands->next;
	}
	ft_list_del(&tmp);
}
