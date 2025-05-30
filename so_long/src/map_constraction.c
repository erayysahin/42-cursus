/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_constraction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:12:08 by erasahin          #+#    #+#             */
/*   Updated: 2024/06/25 21:12:10 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*put_line(char *buffer, int *bf, t_game *sl)
{
	char	*line;
	int		buffer_index;
	int		line_length;
	int		index;

	buffer_index = (*bf);
	line_length = 0;
	index = buffer_index;
	while (buffer[buffer_index] != '\n' && buffer[buffer_index] != '\0')
	{
		line_length++;
		buffer_index++;
	}
	(*bf) += line_length + 1;
	buffer_index = index;
	index = 0;
	line = (char *)malloc(sizeof(char) * (line_length + 1));
	if (!line)
		free_game(sl);
	while (index < line_length)
		line[index++] = buffer[buffer_index++];
	line[index] = '\0';
	return (line);
}

static int	count_nl(char *buffer, int size)
{
	int	enter;
	int	i;

	i = 0;
	enter = 0;
	while (i < size)
	{
		if (buffer[i] == '\n')
			enter++;
		i++;
	}
	return (enter + 1);
}

static char	**map_builder(char *buffer, int size, t_game *sl)
{
	int		index;
	int		bf;
	char	**map;

	index = 0;
	bf = 0;
	sl->map_height = count_nl(buffer, size);
	map = (char **)malloc (sizeof(char *) * sl->map_height);
	if (!map)
		free_game(sl);
	while (index < sl->map_height)
	{
		map[index] = put_line(buffer, &bf, sl);
		index++;
	}
	return (map);
}

char	**map_constractor(t_game *game, int fd)
{
	char	buffer[SIZE];
	int		i;
	int		bytes;

	bytes = 1;
	i = 0;
	ft_reset(buffer);
	while (bytes)
	{
		if (i == SIZE)
		{
			close(fd);
			write(1, "ERROR\n", 6);
			exit(1);
		}
		bytes = read(fd, &buffer[i], 1);
		if (bytes == -1)
		{
			close(fd);
			write(1, "ERROR\n", 6);
			exit(1);
		}
		i++;
	}
	return (map_builder(buffer, i, game));
}
