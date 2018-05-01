#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/includes/libft.h"
#include "libft/includes/ft_printf.h"
#include <unistd.h>		//fork, execve, chdir,access, getcwd
#include <signal.h>		//signal, kill
#include <sys/types.h>		//wait, fork
#include <sys/wait.h>		//wait
#include <sys/time.h>		//
#include <sys/resource.h>	//wait3, wait4
#include <stdlib.h>		//exit
#include <errno.h>

//typedef	(int*)t_pfb(char*, char**);

typedef enum {
	CD,
	BUILT
} t_built;

typedef struct s_cmd_list
{
	char **argv;
	struct s_cmd_list *next;
} t_cmd_list;

char	**parser(char *line/*, char **envp*/);
char	*ft_find(char *name, char **envp);
char	*get_env(char *needle, char **envp);
int	ft_cd(char *path, char**envp);
#endif
