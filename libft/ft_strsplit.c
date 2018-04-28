/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:43:18 by gvynogra          #+#    #+#             */
/*   Updated: 2017/11/23 09:27:54 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static	size_t		word_len(char const *s, int start, char c)
{
	size_t		len;

	len = 0;
	while (s[start] && s[start] == c)
		start++;
	while (s[start] && s[start] != c)
	{
		len++;
		start++;
	}
	return (len);
}

static	size_t		words_count(char const *s, char c)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

char				**ft_strsplit(char const *s, char c)
{
	char		**arr;
	size_t		i;
	size_t		counter;

	i = 0;
	counter = 0;
	if (s && c)
	{
		arr = (char**)malloc(sizeof(char*) * words_count(s, c) + 1);
		if (!arr)
			return (NULL);
		while (i < words_count(s, c) && s[counter])
		{
			while (s[counter] == c)
				counter++;
			arr[i] = ft_strsub(s, counter, word_len(s, counter, c));
			counter += word_len(s, counter, c);
			counter++;
			i++;
		}
		arr[i] = NULL;
		return (arr);
	}
	return (NULL);
}
