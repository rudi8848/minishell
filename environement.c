/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 15:05:12 by gvynogra          #+#    #+#             */
/*   Updated: 2018/05/12 15:05:15 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_copy_env(char *needle, char **g_envp, int warning)
{
	char	*res;
	size_t	len;
	int		i;

	res = NULL;
	i = 0;
	len = ft_strlen(needle);
	while (g_envp[i] != NULL)
	{
		if (ft_strnequ(needle, g_envp[i], len) && g_envp[i][len] == '=')
		{
			res = g_envp[i] + (len + 1);
			return (res);
		}
		i++;
	}
	if (!res)
	{
		if (!warning)
			ft_printf("Environement element %s not found\n", needle);
		return (NULL);
	}
	return (res);
}

int		env_size(char **g_envp)
{
	int i;

	i = 0;
	while (g_envp[i] != NULL)
		i++;
	return (i);
}

char	*get_current_wd(void)
{
	char	buf[2048 + 1];
	char	*dest;

	dest = getcwd(buf, 2048);
	return (dest);
}

char	*ft_path_substitute(char *path, char **g_envp)
{
	char	*dest;
	char	*tmp;

	dest = NULL;
	tmp = NULL;
	if (!path || path[0] == '~' || ft_strequ(path, "--"))
	{
		if (get_copy_env("HOME", g_envp, OK))
			tmp = ft_strdup(get_copy_env("HOME", g_envp, MUTE));
		if (!path || !path[1] || ft_strequ(path, "--"))
			return (tmp);
		dest = ft_strjoin(tmp, path + 1);
		free(tmp);
	}
	return (dest);
}

void	ft_move_env(char ***g_envp, int i, int find)
{
	if (find)
	{
		while (*(*g_envp + i) != NULL)
		{
			if (*(*g_envp + i) != NULL)
				free(*(*g_envp + i));
			if (!*(*g_envp + i + 1))
				*(*g_envp + i) = NULL;
			else
				*(*g_envp + i) = ft_strdup(*(*g_envp + i + 1));
			i++;
		}
	}
}
