/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 15:04:59 by gvynogra          #+#    #+#             */
/*   Updated: 2018/05/12 15:05:01 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(char **args, char ***envp)
{
	int i = 1;
	int j;
	char *ptr;
	while (args[i])
	{

		j = 0;
		while (args[i][j])
		{

			if ((args[i][0] != '$' && args[i][j] != '\"' && args[i][j] != '\'') ||
				(args[i][j] == '\'' && ft_isalpha(args[i][j - 1]) && ft_isalpha(args[i][j + 1])))
				ft_putchar(args[i][j]);
			else if (args[i][0] == '$')
			{
				ptr = get_copy_env(args[i] + 1, *envp);
				if (ptr)
					ft_printf("%s", ptr);
				j += ft_strlen(args[i]);
			}
			j++;
		}
		if (args[i + 1])
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	return 0;
}

int	ft_cd(char **args, char ***envp)
{
	int	ret = 0;
	int i = 0;
	char	*new;
	char	*ptr;
	char	*arr[4];
	char	*old;

	new = NULL;
	ptr = NULL;
	if (ft_strequ(".", args[1]))
		return (ret);
	else if (! args[1] || args[1][0] == '~')
		new = ft_path_substitute(args[1], *envp);
	else
		new = ft_strdup(args[1]);
	old = ft_strdup(get_current_wd());
	ret = chdir(new);

	free(new);
	if (ret == OK)
	{
		new = ft_strdup(get_current_wd());
		arr[0] = "setenv";
		arr[1] = "PWD";
		arr[2] = new;
		arr[3] = NULL;
		if (get_copy_env("PWD", *envp))
			ft_unsetenv(arr, envp);
		ft_setenv(arr, envp);
		arr[1] = "OLDPWD";
		arr[2] = old;
		if (get_copy_env("OLDPWD", *envp))
			ft_unsetenv(arr, envp);
		ft_setenv(arr, envp);
		free(new);
	}	
	else
		printf("cd error\n");
	free(old);
	return ret;
}

int		ft_setenv(char **args, char ***envp)
{
	char *var;
	char **new_envp;
	int		size;
	int i = 0;
	char *str;
	int len;

	if (!args[1] || (args[2] && args[3]))
	{
		ft_printf("setenv: Wrong number of arguments\n");
		return (0);
	}
	else
	{
		str = ft_strjoin(args[1], "=");
			if (args[2])
		{
			var = ft_strjoin(str, args[2]);
			free(str);
			str = ft_strdup(var);
			free(var);
		}
		len = ft_strlen(args[1]);
		size = env_size(*envp);
		while (i < size)
		{
			if (ft_strnequ(args[1], *(*envp +i), len))
			{
				free(*(*envp +i));
				*(*envp +i) = ft_strdup(str);
				free(str);
				return (0);
			}
			i++;
		}
		new_envp = (char**)ft_memalloc(sizeof(char*) * (size + 2));
		if (!new_envp)
		{
			ft_printf("Cannot allocate memory\n");
			return (0);
		}
		i = 0;
		while (i < size)
		{
			new_envp[i] = ft_strdup(*(*envp +i));
			i++;
		}
		new_envp[size] = ft_strdup(str);
		free(str);
		if (new_envp[size] == NULL)
		{
			printf("Cannot set env\n");
			ft_exit(args, envp);
		}
		new_envp[size + 1] = NULL;
		free_arr(*envp);
		*envp = new_envp;
	}
	return 0;
}

int		ft_unsetenv(char **args, char ***envp)
{
	int i;
	int	len;
	int	find;

	find = 0;

	if (args[1])
	{
		len = ft_strlen(args[1]);
		if (ft_strnequ(args[1], "HOME", len) || ft_strnequ(args[1], "LOGNAME", len))
		{
			ft_printf("Cannot unset: premission denied\n");
			return (0);
		}
		i = 0;
		while (*(*envp + i) != NULL || *(*envp + i + 1) != NULL)
		{
			if (ft_strnequ(args[1], *(*envp +i), len))
				{
					find = 1;
					break;
				}
			i++;
		}
	if (find)
	{
		while (*(*envp + i) != NULL)
		{
			if (*(*envp + i) != NULL)
				free(*(*envp + i));
			if (! *(*envp + i + 1))
				*(*envp + i) = NULL;
			else
				*(*envp + i) = ft_strdup(*(*envp + i + 1));
			i++;
		}
	}
}
	return 0;
}

int		ft_env(char **args, char ***envp)
{
	int i = 0;
	while (*(*envp +i) != NULL)
	{
			ft_printf("%s\n", *(*envp +i));
		i++;
	}
	return (0);
}
