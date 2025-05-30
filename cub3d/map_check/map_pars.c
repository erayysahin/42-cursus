/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:15:42 by erasahin          #+#    #+#             */
/*   Updated: 2024/12/25 15:14:31 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../gnl/get_next_line.h"
#include "../libft/srcs/libft.h"
#include "../safe_allocation/s_malloc.h"
#include <fcntl.h>

void	map_dup(int fd, t_data *data, int i)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		program_exit("INVALID_MAP", -1);
	while (line)
	{
		add_garbage_c(line);
		if (ft_strchr(line, '1') || ft_strchr(line, '0'))
		{
			while (line)
			{
				ft_strlcpy(data->map[i++], line, ft_strlen(line) + 1);
				line = get_next_line(fd);
				if (line)
					add_garbage_c(line);
			}
		}
		if (line && !ft_strchr(line, '1') && !ft_strchr(line, '0')
			&& line_control(line))
			program_exit("INVALID_MAP", -1);
		line = get_next_line(fd);
	}
}

void	texture_pars(int fd, t_data *data, int count, char *line)
{
	count = 0;
	while (count < 6)
	{
		line = get_next_line(fd);
		if (!line)
			program_exit("INVALID_MAP", -1);
		add_garbage_c(line);
		if (!ft_strncmp(line, "NO", 2))
			change_texture(line, &count, &data->no);
		else if (!ft_strncmp(line, "SO", 2))
			change_texture(line, &count, &data->so);
		else if (!ft_strncmp(line, "WE", 2))
			change_texture(line, &count, &data->we);
		else if (!ft_strncmp(line, "EA", 2))
			change_texture(line, &count, &data->ea);
		else if (!ft_strncmp(line, "F", 1))
			change_texture_2(line, &count, data->f);
		else if (!ft_strncmp(line, "C", 1))
			change_texture_2(line, &count, data->c);
		else if (line_control(line))
			program_exit("INVALID_MAP", -1);
	}
	texture_check(&data, count);
}

int	map_size2(char *line, t_data *data, int fd)
{
	int	size;

	size = 0;
	while (*line)
	{
		size++;
		if (data->size < (int)ft_strlen(line))
		{
			data->size = (int)ft_strlen(line);
		}
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
	}
	return (size);
}

int	map_size(int fd, t_data *data)
{
	char	*line;
	int		count;
	int		space;

	line = get_next_line(fd);
	count = 0;
	while (line)
	{
		space = ft_isspace(line);
		if (space == (int)ft_strlen(line))
			;
		else if (count < 6 && (ft_strncmp(line, "NO", 2) || ft_strncmp(line,
					"SO", 2) || ft_strncmp(line, "WE", 2) || ft_strncmp(line,
					"EA", 2) || ft_strncmp(line, "F", 1) || ft_strncmp(line,
					"C", 1)))
			count++;
		else if (ft_strchr(line, '1') || ft_strchr(line, '0'))
			return (map_size2(line, data, fd));
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
