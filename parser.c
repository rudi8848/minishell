#include "minishell.h"

char	*get_env(char *needle, char **envp)
{
//	printf("---> %s\n", __FUNCTION__);
	char	*res;
	size_t	len;

	len = ft_strlen(needle);
	while (*envp != NULL)
	{
		if (ft_strnequ(needle, *envp, len))
		{
			res = ft_strsub(*envp, len + 1, ft_strlen(*envp));
			//printf("%s: %s\n", __FUNCTION__, res);
			return (res);
		}
		envp++;
	}
	if (!res)
	{
		ft_printf("Environement element %s not found\n", needle);
		exit(0);
	}
	return (res);
}

char	*ft_find(char *name, char **envp)
{
//	printf("---> %s\n", __FUNCTION__);
	int	find;
	char	*valid_command = NULL;
	char	**path_arr;
	char	*env_path;
	char	*tmp;

	if ((find = access(name, F_OK)) != 0)
	{
		env_path = get_env("PATH", envp);
		path_arr = ft_strsplit(env_path, ':');
		while (*path_arr != NULL)
		{
	//		printf("--> %s: loop\n", __FUNCTION__);
			tmp = ft_strjoin(*path_arr, "/");
			find = access(ft_strcat(tmp, name), X_OK);
	//		printf("%s\n", tmp);
			if (find == 0)
			{
			//	printf("OK\n");
				valid_command = tmp;
			return (valid_command);
			}
			path_arr++;
		}
	}
	else
		valid_command = name;
	if (!valid_command)
	{
		ft_printf("Command %s: not found\n", name);
		return (NULL);
	}
	return (valid_command);
}

char	**parser(char *line)
{
//	printf("---> %s, line: %s\n", __FUNCTION__, line);
	//char	**command;
if (ft_strlen(line) > 1)
{
	command = ft_strsplit(line, ' ');

	/*
	int i = 0;
	int ok = 0;
	while (*command[i])
	{
		printf("in loop %c\n", *command[i]);
		if (ft_isalnum(*command[i]))
			ok++;
		i++;
		printf("%d, %d\n", ok, i);
	}
	if (!command)
	{
		ft_printf("Error: cannot parse command\n");
		exit(0);
	}
	if (ok)*/
		command[0] = ft_find(command[0], envp);
//	printf("%s, %s\n", __FUNCTION__, command[0]);
if (commands)
	return (commands);
}
return (NULL);
}
