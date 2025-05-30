/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:12:28 by erasahin          #+#    #+#             */
/*   Updated: 2024/06/25 21:12:30 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../mlx/mlx.h"

void	ft_reset(char *buffer)
{
	int	i;

	i = 0;
	while (i < SIZE)
		buffer[i++] = 0;
}

int	ft_strlen(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	xpm_control(t_game *game)
{
	int	hero;
	int	wall;
	int	coin;
	int	exitt;
	int	floor;

	(void)game;
	hero = open("./res/hero.xpm", O_RDONLY);
	wall = open("./res/wall.xpm", O_RDONLY);
	coin = open("./res/coin.xpm", O_RDONLY);
	exitt = open("./res/exit.xpm", O_RDONLY);
	floor = open("./res/floor.xpm", O_RDONLY);
	close(hero);
	close(wall);
	close(coin);
	close(exitt);
	close(floor);
	if (hero <= 0 || wall <= 0 || coin <= 0 || exitt <= 0 || floor <= 0)
		free_game(game);
	return (0);
}

void	start_game2(int fd, t_game	*game)
{
	game->map = map_constractor(game, fd);
	close(fd);
	if (map_validation(game))
		free_game(game);
	game->mlx = mlx_init();
	if (!game->mlx)
		free_game(game);
	game->mlx_win = mlx_new_window(game->mlx, game->map_width * PIXEL,
			game->map_height * PIXEL, "so_long");
	if (!game->mlx_win)
		free_game(game);
	xpm_control(game);
	load_sprite(game);
	mlx_hook(game->mlx_win, 2, 0, key_down, game);
	mlx_hook(game->mlx_win, 17, 0, game_exit, game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_loop(game->mlx);
}
