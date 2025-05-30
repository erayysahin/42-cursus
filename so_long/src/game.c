/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:11:49 by erasahin          #+#    #+#             */
/*   Updated: 2024/06/25 21:11:53 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "so_long.h"

void	*add_image(t_game *game, char *path)
{
	int		tmp_x;
	int		tmp_y;
	void	*img;

	img = mlx_xpm_file_to_image(game->mlx, path, &tmp_x, &tmp_y);
	if (!img)
	{
		game_exit(game);
	}
	return (img);
}

void	load_sprite(t_game *game)
{
	game->hero_sprite = add_image(game, "./res/hero.xpm");
	game->wall_sprite = add_image(game, "./res/wall.xpm");
	game->floor_sprite = add_image(game, "./res/floor.xpm");
	game->coin_sprite = add_image(game, "./res/coin.xpm");
	game->exit_sprite = add_image(game, "./res/exit.xpm");
}

static int	filename_check(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (str[i] == 'r'
		&& str[i - 1] == 'e' && str[i - 2] == 'b' && str[i - 3] == '.')
	{
		return (0);
	}
	write(1, "ERROR\n", 6);
	return (1);
}

static void	game_init(t_game *game)
{
	game->hero_sprite = 0;
	game->floor_sprite = 0;
	game->wall_sprite = 0;
	game->coin_sprite = 0;
	game->exit_sprite = 0;
	game->coins = 0;
	game->exit = 0;
	game->ply = 0;
	game->moves = 0;
}

void	start_game(char *map_name, t_game *game)
{
	int	fd;

	if (filename_check(map_name))
		return ;
	game_init(game);
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
	{
		write(1, "error\n", 6);
		exit(1);
	}
	start_game2(fd, game);
}
