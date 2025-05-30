/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 08:40:13 by erasahin          #+#    #+#             */
/*   Updated: 2024/06/26 08:40:15 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_strcount(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	if (s[i] == '\0')
		return (0);
	count = 1;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static int	ft_charcount(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_no_malloc(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		x;
	int		y;

	ptr = (char **)malloc(sizeof(char *) * (ft_strcount(s, c) + 1));
	if (!ptr)
		return (NULL);
	x = -1;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			ptr[++x] = (char *)malloc(sizeof(char) * (ft_charcount(s, c) + 1));
			if (!ptr[x])
				return (ft_no_malloc(ptr));
			y = 0;
			while (*s && *s != c)
				ptr[x][y++] = *s++;
			ptr[x][y] = '\0';
		}
	}
	ptr[++x] = NULL;
	return (ptr);
}

void	free_data(char **data)
{
	int	i;

	i = -1;
	while (data[++i])
		free(data[i]);
	free(data);
}
