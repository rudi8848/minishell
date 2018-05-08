#include "minishell.h"

//extern char **environ;

int		ft_echo(char **args, char **envp)
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
				ptr = get_copy_env(args[i] + 1, envp);
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
/*
char	*get_prev_dir(char	*path, char **envp)
{
	printf("---> %s, %s\n", __FUNCTION__, path);
	size_t	len;
	char	*tmp;
	char	*dest;
	
	tmp = get_current_wd();
	printf("---> tmp: %s\n", tmp);
	len = ft_strlen(tmp);
	len--;
	while (tmp[len] && tmp[len] != '/')
		len--;
	if (!len)
		len = 1;
	dest = ft_strsub(tmp, 0, len);
	printf("---> dest: %s\n", dest);
	return(dest);
}
*/
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


int	ft_cd(char **args, char **envp)
{
//	printf("%s\n", __FUNCTION__);
	int	ret = 0;
	int i = 0;
	char	*new;
	char	*ptr;

	new = NULL;
	ptr = NULL;
	if (ft_strequ(".", args[1]))
		return (ret);
	else if (! args[1] || args[1][0] == '~')
		new = ft_path_substitute(args[1], envp);
	else
		new = args[1];
//	printf("%s %s\n", __FUNCTION__, new);
	ret = chdir(new);

//	free(new);
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
		new = get_current_wd();
//		printf("--> new: %s\n", new);
		*envp = ft_strjoin("PWD=", new);
	//	free(ptr);
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

int		ft_setenv(char **args, char **envp)
{
	printf("%s %s %s %s\n", __FUNCTION__, args[0], args[1], args[2]);
	char *var;
	char **new_envp;
	int		size;
	int i = 0;

	printf("%s\n", args[1]);
	if (args[3] != NULL || !args[1])
	{
		ft_printf("setenv: Wrong number of arguments\n");
		return (0);
	}
	else
	{
		if ((var = get_orig_env(args[1], envp)) != NULL)
		{
			var = ft_strcat(args[1], args[2]);
			printf("%s\n", var);
		}
		else
		{
			size = env_size(envp);
			//
			printf("%d\n",size );
			//
			new_envp = (char**)ft_memalloc(sizeof(char) * (size + 2));
			if (!new_envp)
			{
				ft_printf("Cannot allocate memory\n");
				return (0);
			}
			//var = ft_strjoin(args[1], "=");
			while (i < size)
			{
				new_envp[i] = envp[i];
				i++;
			}
		
			
	printf("after loop, argv[1]: %s\n", args[1]);
		if (args[2])
			new_envp[size] = ft_strjoin(args[1], args[2]);
		else
			new_envp[size] = args[1];
			new_envp[size +1] = NULL;
			envp = new_envp;
		}
	}
	return 0;
}

int		ft_unsetenv(char **args, char **envp)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int		env_size(char **envp)
{
	int i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}
int		ft_env(char **args, char **envp)
{
	printf("%s\n", __FUNCTION__);
	int i = 0;
	while (envp[i] != NULL)
	{
			ft_printf("%s\n", envp[i]);
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
