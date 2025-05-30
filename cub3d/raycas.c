/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:52:19 by erasahin          #+#    #+#             */
/*   Updated: 2024/12/25 13:04:21 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	compute_ray_properties(t_data *data, int x)
{
	data->game.ray_screen_x = 2 * x / (double)WIDTH - 1;
	data->game.ray_direction[0] = data->game.dir[0] + data->game.camera_plane[0]
		* data->game.ray_screen_x;
	data->game.ray_direction[1] = data->game.dir[1] + data->game.camera_plane[1]
		* data->game.ray_screen_x;
	data->game.grid_pos[0] = (int)data->pos[0];
	data->game.grid_pos[1] = (int)data->pos[1];
	if (data->game.ray_direction[0] == 0)
		data->game.grid_step_dist[0] = 1e30;
	else
		data->game.grid_step_dist[0] = fabs(1 / data->game.ray_direction[0]);
	if (data->game.ray_direction[1] == 0)
		data->game.grid_step_dist[1] = 1e30;
	else
		data->game.grid_step_dist[1] = fabs(1 / data->game.ray_direction[1]);
}

void	compute_ray_step_and_distance(t_data *data)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (data->game.ray_direction[i] < 0)
		{
			data->game.ray_step[i] = -1;
			data->game.border_dist[i] = (data->pos[i] - data->game.grid_pos[i])
				* data->game.grid_step_dist[i];
		}
		else
		{
			data->game.ray_step[i] = 1;
			data->game.border_dist[i] = (data->game.grid_pos[i] + 1.0
					- data->pos[i]) * data->game.grid_step_dist[i];
		}
		++i;
	}
}

void	calculate_collision_distance(t_data *data)
{
	int	next_grid_boundary;

	while (1)
	{
		if (data->game.border_dist[0] < data->game.border_dist[1])
			next_grid_boundary = 0;
		else
			next_grid_boundary = 1;
		data->game.border_dist[next_grid_boundary]
			+= data->game.grid_step_dist[next_grid_boundary];
		data->game.grid_pos[next_grid_boundary]
			+= data->game.ray_step[next_grid_boundary];
		if ((data->map[data->game.grid_pos[1]][data->game.grid_pos[0]]) == '1')
		{
			data->game.hit_axis = next_grid_boundary;
			break ;
		}
	}
}

void	compute_wall_dimensions_and_texture(t_data *data)
{
	data->game.perp_wall_dist = data->game.border_dist[data->game.hit_axis]
		- data->game.grid_step_dist[data->game.hit_axis];
	data->game.wall_height = (int)(HEIGHT / data->game.perp_wall_dist);
	data->game.wall_top_pixel = -data->game.wall_height / 2 + HEIGHT / 2;
	if (data->game.wall_top_pixel < 0)
		data->game.wall_top_pixel = 0;
	data->game.wall_bot_pixel = data->game.wall_height / 2 + HEIGHT / 2;
	if (data->game.wall_bot_pixel >= HEIGHT)
		data->game.wall_bot_pixel = HEIGHT - 1;
	data->game.hit_point_x = data->pos[!data->game.hit_axis]
		+ data->game.perp_wall_dist
		* data->game.ray_direction[!data->game.hit_axis];
	data->game.hit_point_x -= (int)data->game.hit_point_x;
	data->game.tex_column[0] = (int)(data->game.hit_point_x * TEXWIDTH);
	if (data->game.hit_axis == 0 && data->game.ray_direction[0] < 0)
		data->game.tex_column[0] = TEXWIDTH - data->game.tex_column[0] - 1;
	else if (data->game.hit_axis == 1 && data->game.ray_direction[1] > 0)
		data->game.tex_column[0] = TEXWIDTH - data->game.tex_column[0] - 1;
	data->game.tex_step = (double)TEXHEIGHT / data->game.wall_height;
	data->game.tex_pos = (data->game.wall_top_pixel - HEIGHT / 2
			+ data->game.wall_height / 2) * data->game.tex_step;
}

void	render_column(t_data *data, int x, int y)
{
	while (++y < HEIGHT)
	{
		data->game.tex_column[1] = data->game.tex_pos;
		if (y < data->game.wall_top_pixel)
			set_pixel_color(data, x, y, (data->c[0] << 16) + (data->c[1] << 8)
				+ data->c[2]);
		else if (y > data->game.wall_bot_pixel)
			set_pixel_color(data, x, y, (data->f[0] << 16) + (data->f[1] << 8)
				+ data->f[2]);
		else
		{
			render_texture(data, x, y);
			data->game.tex_pos += data->game.tex_step;
		}
	}
}
