/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:29:39 by erasahin          #+#    #+#             */
/*   Updated: 2024/12/11 17:37:02 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minilibX/mlx.h"
#include <stdio.h>

void	mlx_free(t_data *data, char *error)
{
	if (data->mlx_data.img.img)
		mlx_destroy_image(data->mlx_data.mlx, data->mlx_data.img.img);
	if (data->mlx_data.north.img)
		mlx_destroy_image(data->mlx_data.mlx, data->mlx_data.north.img);
	if (data->mlx_data.win)
		mlx_destroy_window(data->mlx_data.mlx, data->mlx_data.win);
	if (data->mlx_data.south.img)
		mlx_destroy_image(data->mlx_data.mlx, data->mlx_data.south.img);
	if (data->mlx_data.west.img)
		mlx_destroy_image(data->mlx_data.mlx, data->mlx_data.west.img);
	if (data->mlx_data.east.img)
		mlx_destroy_image(data->mlx_data.mlx, data->mlx_data.east.img);
	if (data->mlx_data.mlx)
		mlx_destroy_display(data->mlx_data.mlx);
	program_exit(error, 0);
}

int	game_quit(t_data *data)
{
	printf("Exit\n");
	mlx_free(data, NULL);
	return (0);
}
