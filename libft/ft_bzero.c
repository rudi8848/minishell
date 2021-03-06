/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 13:14:50 by gvynogra          #+#    #+#             */
/*   Updated: 2017/11/06 13:15:15 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	char				*ptr;
	size_t				i;

	i = 0;
	ptr = s;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}
