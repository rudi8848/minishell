#include "minishell.h"

//extern char **environ;

int		ft_echo(char **args, char **envp)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

char	*get_prev_dir(char	*path, char **envp)
{
	size_t	len;
	char	*tmp;
	char	*dest;

	tmp = get_copy_env("PWD", envp);
	len = ft_strlen(tmp);
	len--;
	while (tmp[len] && tmp[len] != '/')
		len--;
	dest = ft_strsub(tmp, 0, len);
	//tmp = ft_strjoin(dest, path + 2);
	return(dest);
}

char	*ft_path_substitute(char *path, char **envp)
{
	char	*dest;
	char	*tmp;
	int		i = 0;


	if (path[0] == '~')
	{
		tmp = get_copy_env("HOME", envp);
		if (!path[1])
			return (tmp);
		dest = ft_strjoin(tmp, path + 1);
			return (dest);
	}
	else
	{
		if (ft_strequ("..", path))
			return(get_prev_dir(path, envp));
		/*
		tmp = path;
		while (*tmp && ft_strnequ("../", tmp, 3))
		{
			tmp += 3;
			i++;
		}
			printf(">> %s\n", tmp);
		while (i && tmp != path)
		{
			tmp = get_prev_dir(tmp, envp);
				printf(">> %s\n", tmp);
			i--;
		}
	
		return (tmp);*/
	}
	return (NULL);
}

int	ft_cd(char **args, char **envp)
{/*
	нужно обработать ".", "..", "~" 
*/
	//printf("%s\n", __FUNCTION__);
	int	ret = 0;
	int i = 0;
	char	*new;
	char	*ptr;


	if (ft_strequ(".", args[1]))
		return (ret);
	else if (args[1][0] == '~' || ft_strnequ("..", args[1], 2))
		args[1] = ft_path_substitute(args[1], envp);
	printf("%s\n", args[1]);
/*
	ret = chdir(args[1]);
	
new = getcwd(new, 0);
	
	if (ret == OK)
	{
		while (*envp)
		{
			if (ft_strnequ("PWD", *envp, 3))
			{
				ptr = *envp;
				break;
			}
			envp++;
		
		}


	if (args[1][0] != '.' && args[1][0] != '~')
	{
		new = getcwd(new, 0);
		*envp = ft_strjoin("PWD=", new);
	}
	else if (ft_strequ(args[1], ".."))
		*envp = get_prev_dir(getcwd(new,0));
	}
	else
		printf("cd error\n");
		*/
	return ret;
}

char	*get_orig_env(char *name, char **envp)
{
	int i = 0;
	int len;
	char *tmp;

	len = ft_strlen(name) + 1;
	tmp = ft_strcat(name, "=");
	while (envp[i] != NULL)
	{
		if (ft_strnequ(tmp, envp[i], len))
			return(envp[i]);
		i++;
	}
	return (NULL);
}

int		ft_setenv(char **args, char **envp)
{
	printf("%s\n", __FUNCTION__);
	char *var;

	//args[1] - name of variable, args[2] - value,  if args != 2 - error: Too many arguments
printf("%s\n", args[1]);
	if (args[3] != NULL)
		ft_printf("setenv: Too many arguments");
	else
	{
	//if there is variable with such name - unset it and then set new
		if ((var = get_orig_env(args[1], envp)) != NULL)
		{
			var = ft_strcat(args[1], args[2]);
			printf("%s\n", var);
		}
		else
		{
			;
		}
	}
	return 0;
}

int		ft_unsetenv(char **args, char **envp)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int		ft_env(char **args, char **envp)
{
	printf("%s\n", __FUNCTION__);
	int i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

int		ft_exit(char **args, char **envp)
{
	printf("%s\n", __FUNCTION__);
	exit(0);
	return 0;
}