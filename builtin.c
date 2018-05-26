/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 15:04:59 by gvynogra          #+#    #+#             */
/*   Updated: 2018/05/13 09:14:34 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(char **args, char ***g_envp)
{
	int			i;
	int			j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (ft_check_symb(args[i], j))
				ft_putchar(args[i][j]);
			else if (args[i][0] == '$')
			{
				ft_printf("%s", ft_env_var(args[i] + 1, *g_envp));
				j += ft_strlen(args[i]);
			}
			j++;
		}
		if (args[i + 1])
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	return (0);
}

int		ft_cd(char **args, char ***g_envp)
{
	int		ret;
	int		i;
	char	*new;
	char	*ptr;
	char	*old;

	i = 0;
	ptr = NULL;
	if (ft_strequ(".", args[1]))
		return (0);
	new = ft_set_new_path(args, g_envp);
	old = ft_strdup(get_current_wd());
	ret = chdir(new);
	free(new);
	if (ret == OK)
		ft_change_env(new, old, g_envp);
	else
		printf("Cannot change directory\n");
	free(old);
	return (ret);
}

int		ft_setenv(char **args, char ***g_envp)
{
	int		size;
	int		i;
	char	*str;
	int		len;

	i = 0;
	if ((str = ft_check_args(args)))
	{
		size = env_size(*g_envp);
		len = ft_strlen(args[1]);
		while (i < size)
		{
			if (ft_strnequ(args[1], *(*g_envp + i), len)
				&& (*(*g_envp + i))[len] == '=')
			{
				free(*(*g_envp + i));
				*(*g_envp + i) = ft_strdup(str);
				free(str);
				return (0);
			}
			i++;
		}
		return (ft_env_rewrite(str, g_envp, size));
	}
	return (0);
}

int		ft_unsetenv(char **args, char ***g_envp)
{
	int		i;
	int		len;
	int		find;

	find = 0;
	if (args[1])
	{
		len = ft_strlen(args[1]);
		i = 0;
		while (*(*g_envp + i) != NULL)
		{
			if (ft_strnequ(args[1], *(*g_envp + i), len)
				&& (*(*g_envp + i))[len] == '=')
			{
				find = 1;
				break ;
			}
			i++;
		}
		ft_move_env(g_envp, i, find);
	}
	return (0);
}

int		ft_env(char **args, char ***g_envp)
{
	char		**envp_cp;
	char		**ptr;
	t_cmd_list	*cmd;

	cmd = NULL;
	if (ft_strequ(args[1], "-i"))
	{
		envp_cp = (char **)ft_memalloc(sizeof(char*) * 2);
		envp_cp[0] = ft_strjoin("PATH=", get_copy_env("PATH", *g_envp, MUTE));
		envp_cp[1] = NULL;
		ptr = ft_cp_array(args + 2);
		push(&cmd, ptr);
		if (ptr)
			executor(cmd, &envp_cp);
		free(envp_cp[0]);
		free(envp_cp);
	}
	else
		ft_print_env(args, g_envp);
	return (0);
}
