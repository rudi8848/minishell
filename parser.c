/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 15:06:04 by gvynogra          #+#    #+#             */
/*   Updated: 2018/05/12 15:06:06 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_path_fitting(t_cmd_list *cmd, char **envp, char **p_arr, int f)
{
	char	*tmp;
	char	*tmp1;
	int		i;

	i = 0;
	while (p_arr[i] != NULL)
	{
		tmp1 = ft_strjoin(p_arr[i], "/");
		tmp = ft_strjoin(tmp1, cmd->args[0]);
		free(tmp1);
		f = access(tmp, X_OK);
		if (f == OK)
		{
			free(cmd->args[0]);
			cmd->args[0] = ft_strdup(tmp);
			free_arr(p_arr);
			free(tmp);
			return (1);
		}
		if (tmp)
			free(tmp);
		i++;
	}
	free_arr(p_arr);
	return (0);
}

int			ft_find(t_cmd_list *commands, char **envp)
{
	char	**path_arr;
	int		find;
	char	*env_path;

	if (!commands->args[0])
		return (0);
	if ((find = access(commands->args[0], X_OK)) != OK)
	{
		env_path = get_copy_env("PATH", envp);
		if (!env_path)
			return (0);
		path_arr = ft_strsplit(env_path, ':');
		if (!path_arr)
			return (0);
		if (!ft_path_fitting(commands, envp, path_arr, find))
		{
			ft_printf("Command %s: not found\n", commands->args[0]);
			return (0);
		}
	}
	return (1);
}

int			ft_valid_str(char *str)
{
	int i;
	int val;

	i = 0;
	val = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != ';')
			val++;
		i++;
	}
	return (val);
}

void		ft_split_cmd(t_cmd_list **commands, char *ptr, char *line)
{
	char		*tmp;
	int			i;
	char		**args;

	i = 0;
	while (line[i] != ';')
		i++;
	ptr = ft_strsub(line, 0, i);
	args = ft_strsplit(ptr, ' ');
	free(ptr);
	push(commands, args);
	ptr = line;
	while (*ptr && ptr != NULL)
	{
		i = 0;
		ptr = ft_strchr(ptr, ';') + 1;
		while (ptr[i] && ptr[i] != ';')
			i++;
		tmp = ft_strsub(ptr, 0, i);
		args = ft_strsplit(tmp, ' ');
		free(tmp);
		push_back(*commands, args);
		ptr += i;
	}
}

t_cmd_list	*parser(char *line)
{
	t_cmd_list	*commands;
	char		*ptr;
	char		**args;

	commands = NULL;
	if (ft_valid_str(line))
	{
		if ((ptr = ft_strchr(line, ';')))
		{
			ft_split_cmd(&commands, ptr, line);
		}
		else
		{
			args = ft_strsplit(line, ' ');
			if (!args)
				return (NULL);
			push(&commands, args);
		}
	}
	if (commands)
		return (commands);
	return (NULL);
}
