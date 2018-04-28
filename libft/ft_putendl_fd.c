/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:57:16 by gvynogra          #+#    #+#             */
/*   Updated: 2017/11/06 15:57:34 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	size_t		i;

	i = 0;
	if (s && fd)
	{
		while (s[i])
			i++;
		write(fd, s, i);
		write(fd, "\n", 1);
	}
}
