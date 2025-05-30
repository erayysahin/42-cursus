/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:12:22 by erasahin          #+#    #+#             */
/*   Updated: 2024/06/25 21:12:24 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map, size_t height)
{
	size_t	i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static char	*ft_strdup(char *a)
{
	int		i;
	char	*ret;

	ret = malloc(sizeof(char) * ft_strlen(a));
	if (!ret)
		return (NULL);
	i = -1;
	while (a[++i])
		ret[i] = a[i];
	ret[i] = '\0';
	return (ret);
}

static int	check_path(t_game *temp, size_t y, size_t x)
{
	if (temp->map[y][x] == '1')
		return (0);
	if (temp->map[y][x] == 'C')
		temp->coins--;
	if (temp->map[y][x] == 'E')
		temp->exit_is_possible = 1;
	temp->map[y][x] = '1';
	if (check_path(temp, y + 1, x))
		return (0);
	if (check_path(temp, y - 1, x))
		return (0);
	if (check_path(temp, y, x + 1))
		return (0);
	if (check_path(temp, y, x - 1))
		return (0);
	return (0);
}

void	temp_init(t_game *temp, t_game *game)
{
	temp->map_height = game->map_height;
	temp->map_width = game->map_width;
	temp->coins = game->coins;
	temp->player_x = game->player_x;
	temp->player_y = game->player_y;
	temp->exit_is_possible = 0;
}

int	flood_fill(t_game *game)
{
	t_game	temp;
	int		i;

	temp_init(&temp, game);
	temp.map = (char **)malloc(temp.map_height * sizeof(char *));
	if (!temp.map)
		return (1);
	i = -1;
	while (++i < temp.map_height)
	{
		temp.map[i] = ft_strdup(game->map[i]);
		if (temp.map[i] == NULL)
		{
			while (--i >= 0)
				free(temp.map[i]);
			return (free(temp.map), 1);
		}
	}
	check_path(&temp, temp.player_y, temp.player_x);
	if (!(temp.exit_is_possible == 1 && temp.coins == 0))
		return (free_map(temp.map, temp.map_height), 1);
	return (free_map(temp.map, temp.map_height), 0);
}
