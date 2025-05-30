/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rota.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:47:31 by erasahin          #+#    #+#             */
/*   Updated: 2024/12/25 12:33:38 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	rotate(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rotation_angle;

	if (data->game.right)
		rotation_angle = data->game.rot;
	else if (data->game.left)
		rotation_angle = -data->game.rot;
	if (data->game.right && data->game.left)
		return ;
	if (data->game.right || data->game.left)
	{
		old_dir_x = data->game.dir[0];
		data->game.dir[0] = data->game.dir[0] * cos(rotation_angle)
			- data->game.dir[1] * sin(rotation_angle);
		data->game.dir[1] = old_dir_x * sin(rotation_angle) + data->game.dir[1]
			* cos(rotation_angle);
		old_plane_x = data->game.camera_plane[0];
		data->game.camera_plane[0] = data->game.camera_plane[0]
			* cos(rotation_angle) - data->game.camera_plane[1]
			* sin(rotation_angle);
		data->game.camera_plane[1] = old_plane_x * sin(rotation_angle)
			+ data->game.camera_plane[1] * cos(rotation_angle);
	}
}
