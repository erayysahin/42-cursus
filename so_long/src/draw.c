/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:11:37 by erasahin          #+#    #+#             */
/*   Updated: 2024/06/25 21:11:46 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../mlx/mlx.h"

static void	render_map_floors(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			mlx_put_image_to_window(game->mlx, game->mlx_win,
				game->floor_sprite, x * PIXEL, y * PIXEL);
			x++;
		}
		y++;
	}
}

static void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->wall_sprite, x * PIXEL, y * PIXEL);
			else if (game->map[y][x] == '0' || game->map[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->floor_sprite, x * PIXEL, y * PIXEL);
			else if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->coin_sprite, x * PIXEL, y * PIXEL);
			else if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->exit_sprite, x * PIXEL, y * PIXEL);
			x++;
		}
		y++;
	}
}

int	render(t_game *game)
{
	mlx_clear_window(game->mlx, game->mlx_win);
	render_map_floors(game);
	render_map(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->hero_sprite, game->player_x * PIXEL, game->player_y * PIXEL);
	return (0);
}

void	free_game(t_game *game)
{
	write(1, "error", 5);
	free_map(game->map, game->map_height);
	exit(1);
}
