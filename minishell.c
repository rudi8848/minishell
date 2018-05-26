/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 15:05:40 by gvynogra          #+#    #+#             */
/*   Updated: 2018/05/12 15:05:42 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	type_prompt(char **g_envp)
{
	char	*user;
	char	*pwd;
	char	*home;
	int		len;
	char	*tmp;

	user = get_copy_env("LOGNAME", g_envp, MUTE);
	pwd = get_current_wd();
	home = get_copy_env("HOME", g_envp, MUTE);
	if (home)
		len = ft_strlen(home);
	if (ft_strnequ(home, pwd, len))
	{
		home = "~";
		tmp = ft_strsub(pwd, len, ft_strlen(pwd) - len);
	}
	else
	{
		home = "";
		tmp = pwd;
	}
	ft_printf("%s%s: %s%s%s>%s ", RED, user, GREEN, home, tmp, RESET);
	if (tmp != pwd)
		ft_strdel(&tmp);
}

char	**copy_env(void)
{
	extern char		**environ;
	int				size;
	char			**copy;
	int				i;

	i = 0;
	size = env_size(environ);
	copy = (char**)ft_memalloc(sizeof(char*) * size + 1);
	if (!copy)
	{
		ft_printf("Error: cannot copy environement\n");
		exit(0);
	}
	while (environ[i])
	{
		copy[i] = ft_strdup(environ[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int		ft_exit(char **args, char ***g_envp)
{
	free_arr(*g_envp);
	ft_printf("---> Program terminated <---\n");
	exit(0);
	return (0);
}

int		main(void)
{
	char		*line;
	int			ret;
	t_cmd_list	*commands;

	ft_printf("%s", CLEAR);
	signal(SIGINT, main_sig_handler);
	g_envp = copy_env();
	while (1)
	{
		type_prompt(g_envp);
		ret = get_next_line(1, &line);
		commands = parser(line);
		free(line);
		if (commands)
			executor(commands, &g_envp);
		if (!ret)
			ft_printf("\n");
	}
	return (0);
}
