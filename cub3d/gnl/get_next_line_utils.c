/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:46:54 by osarikay          #+#    #+#             */
/*   Updated: 2024/12/16 16:49:39 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup2(const char *buffer)
{
	char	*stack;
	int		i;

	i = 0;
	stack = (char *)malloc(ft_strlen(buffer) + 1);
	if (!stack)
		return (NULL);
	while (*buffer)
		stack[i++] = *buffer++;
	stack[i] = '\0';
	return (stack);
}

char	*ft_strjoin(char const *stack, char const *buffer)
{
	size_t	i;
	char	*new_string;

	if (!stack || !buffer)
		return (NULL);
	new_string = (char *)malloc(ft_strlen(stack) + ft_strlen(buffer) + 1);
	if (!new_string)
		return (NULL);
	i = 0;
	while (*stack)
		new_string[i++] = *stack++;
	while (*buffer)
		new_string[i++] = *buffer++;
	new_string[i] = '\0';
	return (new_string);
}

char	*ft_substr(char const *stack, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (!stack || len <= 0)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = start;
	j = 0;
	while (i < len && j < len)
	{
		new[j] = stack[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

void	*ft_free_stack(char **stack, int create_line)
{
	char	*line;

	if (!*stack)
		return (NULL);
	if (!create_line)
	{
		if (*stack)
		{
			free(*stack);
			*stack = NULL;
		}
		return (NULL);
	}
	else if (create_line)
	{
		line = ft_strdup2(*stack);
		free(*stack);
		*stack = NULL;
		return (line);
	}
	return (NULL);
}
