/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 17:44:37 by gvynogra          #+#    #+#             */
/*   Updated: 2018/05/25 17:44:59 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_set_new_path(char **args, char ***g_envp)
{
	char	*new;

	if (!args[1] || args[1][0] == '~' || ft_strequ(args[1], "--"))
		new = ft_path_substitute(args[1], *g_envp);
	else if (args[1][0] == '-')
	{
		if (!get_copy_env("OLDPWD", *g_envp, OK))
			return (NULL);
		new = ft_strdup(get_copy_env("OLDPWD", *g_envp, MUTE));
	}
	else
		new = ft_strdup(args[1]);
	return (new);
}

char	**ft_cp_array(char **src)
{
	char	**dest;
	int		i;
	int		n;

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

int		ft_print_env(char **args, char ***g_envp)
{
	int i;

	i = 0;
	while (*(*g_envp + i) != NULL)
	{
		ft_printf("%s\n", *(*g_envp + i));
		i++;
	}
	return (0);
}

int		ft_check_dir(char *name)
{
	int				ret;
	struct stat		buf;

	ret = lstat(name, &buf);
	if (ret >= 0)
	{
		if (S_ISDIR(buf.st_mode))
			return (1);
	}
	else
		ft_printf("cannot access %s\n", name);
	return (0);
}

void	main_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("\n");
		type_prompt(g_envp);
	}
}
