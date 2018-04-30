#include "minishell.h"

//extern char **environ;

int	ft_cd(char *path, char **envp)
{
	int	ret;
	char	*new;
	char	*ptr;

	ret = chdir(path);
	if (ret > -1)
	{
		ptr = get_env("PWD", envp);
		new = ft_strjoin("PWD=", path);
		ptr = new;
	}
	else
		printf("cd error\n");
	return ret;
}
