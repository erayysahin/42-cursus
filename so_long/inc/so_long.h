/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:12:39 by erasahin          #+#    #+#             */
/*   Updated: 2024/06/25 21:12:42 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define PIXEL 64
# define SIZE 1000

typedef struct s_game
{
	void			*mlx;
	void			*mlx_win;

	void			*hero_sprite;
	void			*floor_sprite;
	void			*wall_sprite;
	void			*coin_sprite;
	void			*exit_sprite;

	int				player_x;
	int				player_y;
	int				map_height;
	int				map_width;

	unsigned int	moves;
	char			**map;

	int				exit;
	int				ply;
	int				coins;

	int				exit_is_possible;
}	t_game;

void				start_game(char *map_name, t_game *game);

int					key_down(int keycode, t_game *game);
int					game_exit(t_game *game);

int					render(t_game *game);

char				**map_constractor(t_game *game, int fd);
int					map_validation(t_game *sl);
int					flood_fill(t_game *game);

int					ft_strlen(char *str);
void				ft_reset(char *buffer);
void				free_map(char **map, size_t height);
void				free_game(t_game *game);
int					xpm_control(t_game *game);
void				start_game2(int fd, t_game *game);
void				load_sprite(t_game *game);
#endif