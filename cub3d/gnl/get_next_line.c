/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:40:48 by osarikay          #+#    #+#             */
/*   Updated: 2024/12/16 16:29:51 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft/srcs/libft.h"
#include <unistd.h>

static char	*ft_copy_to_stack(char *stack, char *buffer)
{
	char	*new;

	new = 0;
	if (!stack && buffer)
	{
		new = ft_strdup2(buffer);
		if (!new)
			return (NULL);
		return (new);
	}
	new = ft_strjoin(stack, buffer);
	ft_free_stack(&stack, 0);
	return (new);
}

static int	is_newline(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (0);
	while (s[++i])
		if (s[i] == '\n')
			return (1);
	return (0);
}

static char	*gets_before_nl(char *stack)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	if (!stack)
		return (NULL);
	while (stack[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	j = 0;
	while (j <= i)
	{
		line[j] = stack[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*new_line(char *stack)
{
	size_t	i;
	char	*new;

	i = 0;
	if (!stack)
		return (NULL);
	while (stack[i] != '\n')
		i++;
	if (stack[i + 1] == '\0')
		return (ft_free_stack(&stack, 0));
	new = ft_substr(stack, i + 1, ft_strlen(stack));
	if (!new)
	{
		ft_free_stack(&stack, 0);
		return (NULL);
	}
	ft_free_stack(&stack, 0);
	return (new);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	long		readval;
	static char	*stack = NULL;
	char		*line;

	line = NULL;
	readval = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free_stack(&stack, 0));
	while (readval > 0)
	{
		readval = read(fd, buffer, BUFFER_SIZE);
		if ((readval <= 0 && !stack) || readval == -1)
			return (ft_free_stack(&stack, 0));
		buffer[readval] = '\0';
		stack = ft_copy_to_stack(stack, buffer);
		if (is_newline(stack))
		{
			line = gets_before_nl(stack);
			if (!line)
				return (ft_free_stack(&stack, 0));
			return (stack = new_line(stack), line);
		}
	}
	return (ft_free_stack(&stack, 1));
}
