/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 15:05:53 by gvynogra          #+#    #+#             */
/*   Updated: 2018/05/12 15:05:56 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/includes/libft.h"
# include "libft/includes/ft_printf.h"
# include "libft/includes/get_next_line.h"
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <stdlib.h>
# include <errno.h>

# define CLEAR "\e[1;1H\e[2J"
# define RESET "\033[0m"
# define GREEN "\033[1;32m"
# define RED "\033[1;31m"
# define OK 0

typedef	int	(*t_pfb) (char**, char***);

typedef enum {
	ECHO,
	CD,
	SETENV,
	UNSETENV,
	ENV,
	EXIT,
	END,
	BUILT
}	t_built;

typedef struct	s_cmd_list
{
	char				**args;
	struct s_cmd_list	*next;
}				t_cmd_list;

t_cmd_list		*parser(char *line);
int				ft_find(t_cmd_list *cmd, char **envp);
char			*get_copy_env(char *needle, char **envp);
char			*get_orig_env(char *needle, char **envp);
int				ft_echo(char **args, char ***envp);
int				ft_cd(char **args, char ***envp);
int				ft_setenv(char **args, char ***envp);
int				ft_unsetenv(char **args, char ***envp);
int				ft_env(char **args, char ***envp);
int				ft_exit(char **args, char ***envp);
int				env_size(char **envp);
char			*get_current_wd(void);
void			free_arr(char **array);
void			executor(t_cmd_list *commands, char ***envp);
char			*ft_path_substitute(char *path, char **envp);
void			push_back(t_cmd_list *head, char **args);
void			push(t_cmd_list **head, char **args);
void			ft_move_env(char ***envp, int i, int find);
char			*ft_check_args(char **args);
void			ft_change_env(char *new, char *old, char ***envp);
char			*ft_env_var(char *s, char **envp);
char			*get_copy_env(char *needle, char **envp);
#endif
