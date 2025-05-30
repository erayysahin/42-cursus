/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:53:53 by erasahin          #+#    #+#             */
/*   Updated: 2024/12/11 17:36:44 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdbool.h>

static bool	east_west(t_data *data)
{
	if (data->rot == 'W')
	{
		data->game.dir[0] = -1;
		data->game.dir[1] = 0;
		data->game.camera_plane[0] = 0;
		data->game.camera_plane[1] = -0.66;
		return (true);
	}
	else if (data->rot == 'E')
	{
		data->game.dir[0] = 1;
		data->game.dir[1] = 0;
		data->game.camera_plane[0] = 0;
		data->game.camera_plane[1] = 0.66;
		return (true);
	}
	return (false);
}

static bool	south_north(t_data *data)
{
	if (data->rot == 'S')
	{
		data->game.dir[0] = 0;
		data->game.dir[1] = 1;
		data->game.camera_plane[0] = -0.66;
		data->game.camera_plane[1] = 0;
		return (true);
	}
	else if (data->rot == 'N')
	{
		data->game.dir[0] = 0;
		data->game.dir[1] = -1;
		data->game.camera_plane[0] = 0.66;
		data->game.camera_plane[1] = 0;
		return (true);
	}
	return (false);
}

bool	check_player(t_data *data)
{
	if (east_west(data))
		return (true);
	if (south_north(data))
		return (true);
	return (false);
}
