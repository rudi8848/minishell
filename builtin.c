#include "minishell.h"

int		ft_echo(char **args, char ***envp)
{
	printf("%s\n", __FUNCTION__);
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

char	*get_current_wd(void)
{
	char	buf[2048 + 1];
	char	*dest;

	dest = getcwd(buf, 2048);
	return (dest);
}

char	*ft_path_substitute(char *path, char **envp)
{
//printf("---> %s, %s\n", __FUNCTION__, path);
	char	*dest;
	char	*tmp;

	dest = NULL;
	tmp = NULL;
	if (!path || path[0] == '~')
	{
		tmp = get_copy_env("HOME", envp);
		if (!path || !path[1])
			return (tmp);
		dest = ft_strjoin(tmp, path + 1);
		//free(path);
	}
	return (dest);
}


int	ft_cd(char **args, char ***envp)
{
//	printf("%s\n", __FUNCTION__);
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
		new = args[1];
	old = ft_strdup(get_current_wd());
	ret = chdir(new);

//	free(new);
	if (ret == OK)
	{
		new = get_current_wd();
		printf("--> new: %s\n", new);
	arr[0] = "setenv";
	arr[1] = "PWD";
	arr[2] = new;
	arr[3] = NULL;
		ft_setenv(arr, envp);
	//	free(ptr);
	arr[1] = "OLDPWD";
	printf("%s OLDPWD %s\n", __FUNCTION__, old);
	arr[2] = old;
	ft_unsetenv(arr, envp);
	ft_setenv(arr, envp);
	}	
	else
		printf("cd error\n");
	//free(new);				doesn't want delete
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

int		ft_setenv(char **args, char ***envp)
{
	printf("%s \n", __FUNCTION__);
	char *var;
	char **new_envp;
	int		size;
	int i = 0;
	char *str;
	int len;

	//printf("args 0, 1, 2: %s, %s, %s\n", args[0], args[1], args[2]);
	if (args[3] != NULL || !args[1])
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
		printf("%s\n", str);
		len = ft_strlen(args[1]);
		size = env_size(*envp);
		while (i < size)
		{
			if (ft_strnequ(args[1], *(*envp +i), len))
			{
				printf("find in list\n");
				free(*(*envp +i));
				*(*envp +i) = ft_strdup(str);
				free(str);
				return (0);
			}
			i++;
		}

		printf("NOT FOUND, str is:  %s\n", str);
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
		printf("new_envp[size]: [%s]\n", new_envp[size]);
		new_envp[size + 1] = NULL;

		free_arr(*envp);

		*envp = new_envp;
		printf("%p\n", *envp);

	}
	return 0;
}

int		ft_unsetenv(char **args, char ***envp)
{
	printf("%s\n", __FUNCTION__);
	int i;
	int	len;
	int	find;

	find = 0;

	if (args[1])
	{
		len = ft_strlen(args[1]);
		i = 0;
		while (*(*envp + i) != NULL || *(*envp + i + 1) != NULL)
		{
			printf("[%d] %s / %s\n", i, args[1], *(*envp + i));
			if (ft_strnequ(args[1], *(*envp +i), len))
				{
					printf("find in list\n");
					find = 1;
					break;
				}
			i++;
		}
	if (find)
	{
		while (*(*envp + i) != NULL/* || *(*envp + i + 1) != NULL*/)
		{
			printf("[%d] / %s\n", i, *(*envp + i));
			if (*(*envp + i) != NULL)
				free(*(*envp + i));
			if (! *(*envp + i + 1))
				*(*envp + i) = NULL;
			else
				*(*envp + i) = ft_strdup(*(*envp + i + 1));
			i++;
		}
		//*(*envp +i) = NULL;
	}
}
		return 0;
}

int		env_size(char **envp)
{
	int i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}
int		ft_env(char **args, char ***envp)
{
	printf("---> %s, %p\n", __FUNCTION__, *envp);
	int i = 0;
	while (*(*envp +i) != NULL)
	{
			ft_printf("%s\n", *(*envp +i));
		i++;
	}
	return (0);
}

int		ft_exit(char **args, char ***envp)
{
	free_arr(*envp);
	printf("%s\n", __FUNCTION__);
	exit(0);
	return 0;
}
