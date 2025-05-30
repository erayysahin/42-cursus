/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:05:57 by erasahin          #+#    #+#             */
/*   Updated: 2024/12/25 15:14:58 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/srcs/libft.h"
#include "../safe_allocation/s_malloc.h"
#include <fcntl.h>

void	change_texture(char *line, int *count, char **data_2)
{
	*data_2 = ft_strdup(line + 2);
	*data_2 = ft_strtrim(*data_2, " \n\t\r\v\f");
	add_garbage_c(*data_2);
	if (open(*data_2, O_RDONLY) < 0)
		program_exit("INVALID_TEXTURE", -1);
	(*count)++;
}

void	change_texture_2(char *line, int *count, int *data_2)
{
	int	i;
	int	count_2;

	i = 0;
	count_2 = 0;
	while (line[i])
	{
		if (line[i] == ',' && line[i + 1] == ',')
			program_exit("INVALID_ELEMENT", -1);
		if (line[i] == ',')
			count_2++;
		i++;
	}
	if (count_2 != 2)
		program_exit("INVALID_ELEMENT", -1);
	if (ft_atoi(line + 1 + ft_isspace(line + 1), data_2))
		program_exit("INVALID_ELEMENT", -1);
	if (data_2[0] < 0 || data_2[0] > 255 || data_2[1] < 0 || data_2[1] > 255
		|| data_2[2] < 0 || data_2[2] > 255)
		program_exit("INVALID_ELEMENT", -1);
	(*count)++;
}

int	line_control(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && !(line[i] >= '\t' && line[i] <= '\r'))
			return (1);
		i++;
	}
	return (0);
}

void	set_pixel_color(t_data *data, int x, int y, int color)
{
	data->mlx_data.img.addr[y * WIDTH + x] = color;
}

void	render_texture(t_data *data, int x, int y)
{
	if (data->game.hit_axis == 1)
	{
		if (data->game.ray_direction[1] < 0)
			set_pixel_color(data, x, y, data->mlx_data.north.addr[TEXHEIGHT
				* data->game.tex_column[1] + data->game.tex_column[0]]);
		else
			set_pixel_color(data, x, y, data->mlx_data.south.addr[TEXHEIGHT
				* data->game.tex_column[1] + data->game.tex_column[0]]);
	}
	else
	{
		if (data->game.ray_direction[0] < 0)
			set_pixel_color(data, x, y, data->mlx_data.west.addr[TEXHEIGHT
				* data->game.tex_column[1] + data->game.tex_column[0]]);
		else
			set_pixel_color(data, x, y, data->mlx_data.east.addr[TEXHEIGHT
				* data->game.tex_column[1] + data->game.tex_column[0]]);
	}
}
