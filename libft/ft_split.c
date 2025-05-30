/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:04:30 by erasahin          #+#    #+#             */
/*   Updated: 2023/12/28 14:03:21 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countword(char const *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static size_t	ft_word_length(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static char	**ft_free_all(char **result, size_t i)
{
	while (i > 0)
		free(result[--i]);
	free(result);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	len;
	size_t	i;

	result = (char **)malloc(sizeof(char *) * (ft_countword(s, c) + 1));
	if (!s || !result)
		return (0);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = ft_word_length(s, c);
			result[i] = ft_substr(s, 0, len);
			if (!result[i])
				return (ft_free_all(result, i));
			i++;
			s += len;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}
