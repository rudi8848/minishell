#include "minishell.h"

char	*get_copy_env(char *needle, char **envp)
{
//	printf("---> %s\n", __FUNCTION__);
	char	*res = NULL;
	size_t	len;
	int		i = 0;

	len = ft_strlen(needle);
	while (envp[i] != NULL)
	{
		if (ft_strnequ(needle, envp[i], len) && envp[i][len] == '=')
		{
			res = envp[i] + (len + 1);
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

void	free_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}

	free(array);
	array = NULL;

}

int		ft_find(t_cmd_list *commands, char **envp)
{
	//printf("---> %s, %s\n", __FUNCTION__, commands->args[0]);
	int	find;
	char	**path_arr;
	char	*env_path;
	char	*tmp;
	char	*tmp1;

	int	i = 0;
	if (!commands->args[0])
		return (0);
	if ((find = access(commands->args[0], X_OK)) != OK)
	{
		env_path = get_copy_env("PATH", envp);
		path_arr = ft_strsplit(env_path, ':');	
		while (path_arr[i] != NULL)
		{
			tmp1 = ft_strjoin(path_arr[i], "/");
			tmp = ft_strjoin(tmp1, commands->args[0]);
			free(tmp1);
			find = access(tmp, X_OK);
			if (find == OK)
			{				
				free(commands->args[0]);
				commands->args[0] = ft_strdup(tmp);
				free_arr(path_arr);
				free(tmp);
				return (1);
			}
			if (tmp)
				free(tmp);
			i++;
		}
		ft_printf("Command %s: not found\n", commands->args[0]);
		free_arr(path_arr);
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
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != ';')
			val++;
		i++;
	}
	return (val);
}

t_cmd_list		*parser(char *line)
{
	//printf("---> %s\n", __FUNCTION__);
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
			free(ptr);
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
			free(tmp);
				push_back(commands, args);		
				ptr += i;
			}
		}
		else
		{
			args = ft_strsplit(line, ' ');
			if (!args)
				return (NULL);
			push(&commands, args);
		}
	}
	if (commands)
		return (commands);
	return (NULL);
}
