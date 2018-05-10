#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/includes/libft.h"
#include "libft/includes/ft_printf.h"
#include "libft/includes/get_next_line.h"
#include <unistd.h>		//fork, execve, chdir,access, getcwd
#include <signal.h>		//signal, kill
#include <sys/types.h>		//wait, fork
#include <sys/wait.h>		//wait
#include <sys/time.h>		//
#include <sys/resource.h>	//wait3, wait4
#include <stdlib.h>		//exit
#include <errno.h>


#define CLEAR "\e[1;1H\e[2J"
#define RESET "\033[0m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define OK 0
typedef	int (*t_pfb) (char**, char***);

typedef enum {
	ECHO,
	CD,
	SETENV,
	UNSETENV,
	ENV,
	EXIT,
	BUILT
} t_built;

typedef struct s_cmd_list
{
	char **args;
	struct s_cmd_list *next;
} t_cmd_list;

t_cmd_list *parser(char *line/*, char **envp*/);
int		ft_find(t_cmd_list *cmd, char **envp);
char	*get_copy_env(char *needle, char **envp);
char	*get_orig_env(char *needle, char **envp);
int		ft_echo(char **args, char ***envp);
int	ft_cd(char **args, char ***envp);
int		ft_setenv(char **args, char ***envp);
int		ft_unsetenv(char **args, char ***envp);
int		ft_env(char **args, char ***envp);
int		ft_exit(char **args, char ***envp);
int		env_size(char **envp);
char	*get_current_wd(void);
void    free_arr(char **array);
#endif
