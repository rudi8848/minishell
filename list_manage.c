/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 12:12:56 by gvynogra          #+#    #+#             */
/*   Updated: 2018/05/13 12:12:58 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void		push_back(t_cmd_list *head, char **args)
{
	t_cmd_list	*last;
	t_cmd_list	*tmp;

	last = get_last(head);
	tmp = (t_cmd_list*)ft_memalloc(sizeof(t_cmd_list));
	tmp->args = args;
	tmp->next = NULL;
	last->next = tmp;
}

void		push(t_cmd_list **head, char **args)
{
	t_cmd_list	*tmp;

	tmp = (t_cmd_list*)ft_memalloc(sizeof(t_cmd_list));
	tmp->args = args;
	tmp->next = (*head);
	(*head) = tmp;
}

void		free_arr(char **array)
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

void		ft_list_del(t_cmd_list **commands)
{
	t_cmd_list	*prev;

	while (*commands)
	{
		prev = (*commands);
		(*commands) = (*commands)->next;
		free_arr(prev->args);
		free(prev);
	}
}
