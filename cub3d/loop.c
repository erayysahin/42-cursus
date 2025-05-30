/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:43:20 by erasahin          #+#    #+#             */
/*   Updated: 2024/12/25 12:32:55 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minilibX/mlx.h"

void	move_player(t_data *data, double _movex, double _movey)
{
	if (data->map[(int)(data->pos[1])][(int)(data->pos[0] + _movex)] != '1')
		data->pos[0] += _movex;
	if (data->map[(int)(data->pos[1] + _movey)][(int)(data->pos[0])] != '1')
		data->pos[1] += _movey;
}

void	handle_movement(t_data *data, double move_x, double move_y)
{
	if (data->key.a)
	{
		move_x = -data->game.camera_plane[0] * data->game.speed;
		move_y = -data->game.camera_plane[1] * data->game.speed;
		move_player(data, move_x, move_y);
	}
	if (data->key.d)
	{
		move_x = data->game.camera_plane[0] * data->game.speed;
		move_y = data->game.camera_plane[1] * data->game.speed;
		move_player(data, move_x, move_y);
	}
	if (data->key.w)
	{
		move_x = data->game.dir[0] * data->game.speed;
		move_y = data->game.dir[1] * data->game.speed;
		move_player(data, move_x, move_y);
	}
	if (data->key.s)
	{
		move_x = -data->game.dir[0] * data->game.speed;
		move_y = -data->game.dir[1] * data->game.speed;
		move_player(data, move_x, move_y);
	}
}

static void	raycast(t_data *data)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		compute_ray_properties(data, x);
		compute_ray_step_and_distance(data);
		calculate_collision_distance(data);
		compute_wall_dimensions_and_texture(data);
		render_column(data, x, -1);
	}
	mlx_put_image_to_window(data->mlx_data.mlx, data->mlx_data.win,
		data->mlx_data.img.img, 0, 0);
}

int	loop(t_data *data)
{
	handle_movement(data, 0, 0);
	rotate(data);
	raycast(data);
	return (0);
}
