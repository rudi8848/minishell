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

int		ft_echo(char **args, char ***envp)
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
				ft_printf("%s", ft_env_var(args[i] + 1, *envp));
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

int		ft_cd(char **args, char ***envp)
{
	int		ret;
	int		i;
	char	*new;
	char	*ptr;
	char	*old;

	i = 0;
	new = NULL;
	ptr = NULL;
	if (ft_strequ(".", args[1]))
		return (0);
	else if (!args[1] || args[1][0] == '~' || ft_strequ(args[1], "--"))
		new = ft_path_substitute(args[1], *envp);
	else if (args[1][0] == '-')
		new = ft_strdup(get_copy_env("OLDPWD", *envp, MUTE));	
	else
		new = ft_strdup(args[1]);
	old = ft_strdup(get_current_wd());
	
	//else if (args[1][0] == '-')
	//	new = ft_strdup(get_copy_env("OLDPWD", *envp));	

	ret = chdir(new);
	free(new);
	if (ret == OK)
		ft_change_env(new, old, envp);
	else
		printf("cd error\n");
	free(old);
	return (ret);
}

int		ft_setenv(char **args, char ***envp)
{
	int		size;
	int		i;
	char	*str;
	int		len;

	i = 0;
	if ((str = ft_check_args(args)))
	{
		size = env_size(*envp);
		len = ft_strlen(args[1]);
		while (i < size)
		{
			if (ft_strnequ(args[1], *(*envp + i), len)
				&& (*(*envp + i))[len] == '=')
			{
				free(*(*envp + i));
				*(*envp + i) = ft_strdup(str);
				free(str);
				return (0);
			}
			i++;
		}
		return (ft_env_rewrite(str, envp, size));
	}
	return (0);
}

int		ft_unsetenv(char **args, char ***envp)
{
	int		i;
	int		len;
	int		find;

	find = 0;
	if (args[1])
	{
		len = ft_strlen(args[1]);
		if (ft_strnequ(args[1], "HOME", len) ||
				ft_strnequ(args[1], "LOGNAME", len))
			return (ft_printf("Cannot unset: premission denied\n"));
		i = 0;
		while (*(*envp + i) != NULL || *(*envp + i + 1) != NULL)
		{
			if (ft_strnequ(args[1], *(*envp + i), len)
				&& (*(*envp + i))[len] == '=')
			{
				find = 1;
				break ;
			}
			i++;
		}
		ft_move_env(envp, i, find);
	}
	return (0);
}

char		**ft_cp_array(char **src)
{
	char	**dest;
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (src[n] != NULL)
		n++;
	dest = (char **)ft_memalloc(sizeof(char *) * (n + 1));
	if (!dest)
		return (NULL);
	while (i < n)
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[n] = NULL;
	return (dest);
}

int		ft_env(char **args, char ***envp)
{
	char **envp_cp;
	char **ptr;
	t_cmd_list *cmd;
	
	cmd = NULL;
	envp_cp = (char **)ft_memalloc(sizeof(char*) * 2);
	envp_cp[0] = ft_strjoin("PATH=", get_copy_env("PATH", *envp, MUTE));
	envp_cp[1] = NULL;
	if (ft_strequ(args[1], "-i"))
	{
		ptr = ft_cp_array(args + 2);
		push(&cmd, ptr);
		if (ptr)
			executor(cmd, &envp_cp);
		free(envp_cp[0]);
		free(envp_cp);
		return 0;
	}
	else
		ft_print_env(args, envp);

}

int		ft_print_env(char **args, char ***envp)
{
	int i;

	i = 0;
	while (*(*envp + i) != NULL)
	{
		ft_printf("%s\n", *(*envp + i));
		i++;
	}
	return (0);
}
