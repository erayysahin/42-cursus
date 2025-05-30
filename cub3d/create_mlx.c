/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:13:33 by erasahin          #+#    #+#             */
/*   Updated: 2024/12/25 14:19:35 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minilibX/mlx.h"
#include "safe_allocation/s_malloc.h"
#include <stdbool.h>

void	mlx_addr(t_data *data, int x)
{
	data->mlx_data.img.addr = (int *)mlx_get_data_addr(data->mlx_data.img.img,
			&x, &x, &x);
	data->mlx_data.north.addr = (int *)mlx_get_data_addr(
			data->mlx_data.north.img, &x, &x, &x);
	data->mlx_data.south.addr = (int *)mlx_get_data_addr(
			data->mlx_data.south.img, &x, &x, &x);
	data->mlx_data.west.addr = (int *)mlx_get_data_addr(data->mlx_data.west.img,
			&x, &x, &x);
	data->mlx_data.east.addr = (int *)mlx_get_data_addr(data->mlx_data.east.img,
			&x, &x, &x);
	if (!data->mlx_data.img.addr || !data->mlx_data.north.addr
		|| !data->mlx_data.south.addr || !data->mlx_data.west.addr
		|| !data->mlx_data.east.addr)
		mlx_free(data, "INVALID_TEXTURE");
}

void	create_image(t_data *data)
{
	int	x;

	data->mlx_data.img.img = mlx_new_image(data->mlx_data.mlx, WIDTH, HEIGHT);
	data->mlx_data.north.img = mlx_xpm_file_to_image(data->mlx_data.mlx,
			data->no, &x, &x);
	data->mlx_data.south.img = mlx_xpm_file_to_image(data->mlx_data.mlx,
			data->so, &x, &x);
	data->mlx_data.west.img = mlx_xpm_file_to_image(data->mlx_data.mlx,
			data->we, &x, &x);
	data->mlx_data.east.img = mlx_xpm_file_to_image(data->mlx_data.mlx,
			data->ea, &x, &x);
	if (!data->mlx_data.img.img || !data->mlx_data.north.img
		|| !data->mlx_data.south.img || !data->mlx_data.west.img
		|| !data->mlx_data.east.img)
		mlx_free(data, "INVALID_TEXTURE");
	mlx_addr(data, x);
}

void	init2(t_data *data)
{
	data->game.grid_step_dist[0] = 0;
	data->game.grid_step_dist[1] = 0;
	data->game.ray_step[0] = 0;
	data->game.ray_step[1] = 0;
	data->game.border_dist[0] = 0;
	data->game.border_dist[1] = 0;
	data->game.hit_axis = 0;
	data->game.perp_wall_dist = 0;
	data->game.wall_height = 0;
	data->game.wall_top_pixel = 0;
	data->game.wall_bot_pixel = 0;
	data->game.hit_point_x = 0;
	data->game.tex_column[0] = 0;
	data->game.tex_column[1] = 0;
	data->game.tex_step = 0;
	data->game.tex_pos = 0;
	data->mlx_data.east = (t_image){0};
	data->mlx_data.north = (t_image){0};
	data->mlx_data.south = (t_image){0};
	data->mlx_data.west = (t_image){0};
	data->mlx_data.img = (t_image){0};
	data->mlx_data.win = 0;
	data->mlx_data.mlx = 0;
}

void	player_init(t_data *data)
{
	data->pos[0] = data->player_xy[0] + 0.5;
	data->pos[1] = data->player_xy[1] + 0.5;
	data->game.player_dir = 0;
	data->game.speed = 0.026;
	data->game.rot = 0.023;
	data->game.left = false;
	data->game.right = false;
	data->game.dir[0] = 0;
	data->game.dir[1] = 0;
	data->game.camera_plane[0] = 0;
	data->game.camera_plane[1] = 0;
	data->game.ray_direction[0] = 0;
	data->game.ray_direction[1] = 0;
	data->game.ray_screen_x = 0;
	data->game.grid_pos[0] = 0;
	data->game.grid_pos[1] = 0;
	init2(data);
}

void	create_mlx(t_data *data)
{
	player_init(data);
	check_player(data);
	data->mlx_data.mlx = mlx_init();
	add_garbage_c(data->mlx_data.mlx);
	data->mlx_data.win = mlx_new_window(data->mlx_data.mlx, WIDTH, HEIGHT,
			"cub3D");
	if (!data->mlx_data.win)
		mlx_free(data, "INVALID_WINDOW");
	create_image(data);
	mlx_hook(data->mlx_data.win, 2, 2, key_press, data);
	mlx_hook(data->mlx_data.win, 3, 3, key_release, data);
	mlx_hook(data->mlx_data.win, 17, 17, game_quit, data);
	mlx_loop_hook(data->mlx_data.mlx, &loop, data);
	mlx_loop(data->mlx_data.mlx);
}
