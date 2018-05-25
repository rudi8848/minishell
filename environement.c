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

char	*get_copy_env(char *needle, char **envp, int warning)
{
	char	*res;
	size_t	len;
	int		i;

	res = NULL;
	i = 0;
	len = ft_strlen(needle);
	while (envp[i] != NULL)
	{
		if (ft_strnequ(needle, envp[i], len) && envp[i][len] == '=')
		{
			res = envp[i] + (len + 1);
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

int		env_size(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
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

int				ft_check_dir(char *name)
{
	int				ret;
	struct stat		buf;

	ret = lstat(name, &buf);
	if (ret >= 0)
	{
		if (S_ISDIR(buf.st_mode))
		/*	ft_read_dir(name, options, head);
		else
			ft_read_file(name, options, buf, head);*/
		return (1);
	}
	else
	{
		ft_printf("cannot access %s\n", name);
	}
	return (0);
}

char	*ft_path_substitute(char *path, char **envp)
{
	char	*dest;
	char	*tmp;

	dest = NULL;
	tmp = NULL;
	if (!path || path[0] == '~' || ft_strequ(path, "--"))
	{
		if (get_copy_env("HOME", envp, OK))
			tmp = ft_strdup(get_copy_env("HOME", envp, MUTE));
		if (!path || !path[1] || ft_strequ(path, "--"))
			return (tmp);
		dest = ft_strjoin(tmp, path + 1);
		free(tmp);
	}
	return (dest);
}

void	ft_move_env(char ***envp, int i, int find)
{
	if (find)
	{
		while (*(*envp + i) != NULL)
		{
			if (*(*envp + i) != NULL)
				free(*(*envp + i));
			if (!*(*envp + i + 1))
				*(*envp + i) = NULL;
			else
				*(*envp + i) = ft_strdup(*(*envp + i + 1));
			i++;
		}
	}
}
