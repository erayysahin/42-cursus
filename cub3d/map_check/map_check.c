/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:22:45 by erasahin          #+#    #+#             */
/*   Updated: 2024/12/25 15:08:42 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/srcs/libft.h"
#include <fcntl.h>
#include <stdio.h>

int	map_check(t_data *data, int i, int j)
{
	if (i < 0 || j < 0 || i >= data->map_size || j > data->size)
		program_exit("INVALID_MAP", -1);
	else if (data->map[i][j] == '1' || data->map[i][j] == '2')
		return (0);
	else if (data->map[i][j] == '0')
	{
		data->map[i][j] = '2';
		if (map_check(data, i + 1, j))
			return (1);
		if (map_check(data, i - 1, j))
			return (1);
		if (map_check(data, i, j + 1))
			return (1);
		if (map_check(data, i, j - 1))
			return (1);
	}
	else
		program_exit("INVALID_MAP", -1);
	return (0);
}

void	line_check(t_data *tmp_data, t_data *data, int i, int *flag)
{
	int	j;

	j = -1;
	while (tmp_data->map[i][++j])
	{
		if (tmp_data->map[i][j] == 'N' || tmp_data->map[i][j] == 'W'
			|| tmp_data->map[i][j] == 'E' || tmp_data->map[i][j] == 'S')
		{
			data->rot = tmp_data->map[i][j];
			data->player_xy[1] = i;
			data->player_xy[0] = j;
			if (*flag)
				program_exit("INVALID_MAP", -1);
			*flag = 1;
			tmp_data->map[i][j] = '0';
			map_check(tmp_data, i, j);
		}
		else if (tmp_data->map[i][j] != '0' && tmp_data->map[i][j] != '2'
			&& tmp_data->map[i][j] != '1' && tmp_data->map[i][j] != ' '
			&& !(tmp_data->map[i][j] >= 7 && tmp_data->map[i][j] <= 13)
			&& tmp_data->map[i][j] != '\0')
			program_exit("INVALID_MAP", -1);
	}
}

void	texture_check(t_data **data, int count)
{
	int	fd;

	if (!(*data)->no || !(*data)->so || !(*data)->we || !(*data)->ea
		|| !(*data)->f[0] || !(*data)->f[1] || !(*data)->f[2] || !(*data)->c[0]
		|| !(*data)->c[1] || !(*data)->c[2] || count != 6)
		program_exit("INVALID_ELEMENT", -1);
	fd = open((*data)->no, O_RDONLY);
	if (fd < 0)
		program_exit("INVALID_TEXTURE", -1);
	close(fd);
	fd = open((*data)->so, O_RDONLY);
	if (fd < 0)
		program_exit("INVALID_TEXTURE", -1);
	close(fd);
	fd = open((*data)->we, O_RDONLY);
	if (fd < 0)
		program_exit("INVALID_TEXTURE", -1);
	close(fd);
	fd = open((*data)->ea, O_RDONLY);
	if (fd < 0)
		program_exit("INVALID_TEXTURE", -1);
	close(fd);
}

void	player_loc(t_data *data)
{
	int	i;
	int	flag;

	flag = 0;
	i = -1;
	while (data->map[++i])
	{
		if (ft_strchr(data->map[i], '2'))
			program_exit("INVALID_MAP", -1);
	}
	i = -1;
	while (data->map[++i])
	{
		line_check(data, data, i, &flag);
	}
	if (!data->rot)
		program_exit("INVALID_MAP", -1);
}
