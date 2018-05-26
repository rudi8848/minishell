/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 12:19:17 by gvynogra          #+#    #+#             */
/*   Updated: 2018/05/13 12:19:19 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_symb(char *s, int index)
{
	if ((s[0] != '$' && s[index] != '\"' && s[index] != '\\' &&
						s[index] != '\'') || (s[index] == '\''
						&& ft_isalpha(s[index - 1])
							&& ft_isalpha(s[index + 1])))
		return (1);
	else
		return (0);
}

char	*ft_env_var(char *s, char **g_envp)
{
	char *ptr;

	if (!(ptr = get_copy_env(s, g_envp, MUTE)))
		ptr = "";
	return (ptr);
}

void	ft_change_env(char *new, char *old, char ***g_envp)
{
	char	*arr[4];

	new = ft_strdup(get_current_wd());
	arr[0] = "setenv";
	arr[1] = "PWD";
	arr[2] = new;
	arr[3] = NULL;
	if (get_copy_env("PWD", *g_envp, MUTE))
		ft_unsetenv(arr, g_envp);
	ft_setenv(arr, g_envp);
	arr[1] = "OLDPWD";
	arr[2] = old;
	if (get_copy_env("OLDPWD", *g_envp, MUTE))
		ft_unsetenv(arr, g_envp);
	ft_setenv(arr, g_envp);
	free(new);
}

char	*ft_check_args(char **args)
{
	char	*var;
	char	*str;

	if (!args[1] || (args[2] && args[3]))
	{
		ft_printf("setenv: Wrong number of arguments\n");
		return (NULL);
	}
	if ((ft_strequ(args[1], "HOME") || ft_strequ(args[1], "PWD")
		|| ft_strequ(args[1], "OLDPWD")) && args[2])
	{
		if (!ft_check_dir(args[2]))
			return (NULL);
	}
	str = ft_strjoin(args[1], "=");
	if (args[2])
	{
		var = ft_strjoin(str, args[2]);
		free(str);
		str = ft_strdup(var);
		free(var);
	}
	return (str);
}

int		ft_env_rewrite(char *str, char ***g_envp, int size)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = (char**)ft_memalloc(sizeof(char*) * (size + 2));
	if (!new_envp)
		return (ft_printf("Cannot allocate memory\n"));
	while (i < size)
	{
		new_envp[i] = ft_strdup(*(*g_envp + i));
		i++;
	}
	new_envp[size] = ft_strdup(str);
	free(str);
	if (new_envp[size] == NULL)
		return (printf("Cannot set env\n"));
	new_envp[size + 1] = NULL;
	free_arr(*g_envp);
	*g_envp = new_envp;
	return (0);
}
