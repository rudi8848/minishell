#include "minishell.h"

//extern char **environ;

int		ft_echo(char **args, char **envp)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

char	*get_prev_dir(char	*path)
{
	int		len;
	char	*res;

	while (path[len] != '/')
		len--;
	res = ft_strsub(path, 0, len);
	return (res);
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
		
	return ret;
}

int		ft_setenv(char **args, char **envp)
{
	printf("%s\n", __FUNCTION__);
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
	return 0;
}

int		ft_exit(char **args, char **envp)
{
	printf("%s\n", __FUNCTION__);
	exit(0);
	return 0;
}