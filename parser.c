#include "minishell.h"

char	*get_copy_env(char *needle, char **envp)
{
//	printf("---> %s\n", __FUNCTION__);
	char	*res;
	size_t	len;
	int		i = 0;

	len = ft_strlen(needle);
	while (envp[i] != NULL)
	{
		if (ft_strnequ(needle, envp[i], len) && envp[i][len] == '=')
		{
			res = ft_strsub(envp[i], len + 1, ft_strlen(envp[i]));
			return (res);
		}
		i++;
	}
	if (!res)
	{
		ft_printf("Environement element %s not found\n", needle);
		return(0);
	}
	return (res);
}

int		ft_find(t_cmd_list *commands, char **envp)
{
	int	find;
	char	**path_arr;
	char	*env_path;
	char	*tmp;

	if (!commands->args[0])
		return (0);
	if ((find = access(commands->args[0], F_OK)) != 0)
	{
		env_path = get_copy_env("PATH", envp);
		path_arr = ft_strsplit(env_path, ':');
		while (*path_arr != NULL)
		{
			tmp = ft_strjoin(*path_arr, "/");
			find = access(ft_strcat(tmp, commands->args[0]), X_OK);
			if (find == 0)
			{
				commands->args[0] = tmp;
				return (1);
			}
			path_arr++;
		}
		ft_printf("Command %s: not found\n", commands->args[0]);
		return (0);
	}
	return (1);
}

t_cmd_list	*get_last(t_cmd_list *head)
{
	if (head == NULL)
	{
		head = (t_cmd_list*)ft_memalloc(sizeof(t_cmd_list));
		if (!head)
			return (NULL);
		return (head);
	}
	while (head->next)
		head = head->next;
	return (head);
}

void	push_back(t_cmd_list *head, char **args)
{
	t_cmd_list	*last;
	t_cmd_list	*tmp;

	last = get_last(head);
	tmp = (t_cmd_list*)ft_memalloc(sizeof(t_cmd_list));
	tmp->args = args;
	tmp->next = NULL;
	last->next = tmp;
}

void	push(t_cmd_list **head, char **args)
{
	t_cmd_list	*tmp;

	tmp = (t_cmd_list*)ft_memalloc(sizeof(t_cmd_list));
	tmp->args = args;
	tmp->next = (*head);
	(*head) = tmp;
}

int		ft_valid_str(char *str)
{
	int i;
	int val;

	i = 0;
	val = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			val++;
		i++;
	}
	return (val);
}

t_cmd_list		*parser(char *line)
{
	t_cmd_list	*commands = NULL;
	char		*ptr;
	char		**args;
	char		*tmp;
	if (ft_valid_str(line))
	{
		if ((ptr = ft_strchr(line, ';')))
		{
			int i = 0;
			while (line[i] != ';')
				i++;
			ptr = ft_strsub(line, 0, i);
			args = ft_strsplit(ptr, ' ');
			push(&commands, args);
			ptr = line;
			while (*ptr && ptr != NULL)
			{
				i = 0;

				ptr = ft_strchr(ptr, ';') + 1;
				while (ptr[i] && ptr[i] != ';')
					i++;
				tmp = ft_strsub(ptr, 0, i);
				args = ft_strsplit(tmp, ' ');
				push_back(commands, args);		
				ptr += i;
			}
		}
		else
		{
			args = ft_strsplit(line, ' ');
			push(&commands, args);
		}
	}
	if (commands)
		return (commands);
	return (NULL);
}
