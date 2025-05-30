/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:29:52 by erasahin          #+#    #+#             */
/*   Updated: 2024/12/11 17:43:14 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		game_quit(data);
	if (keycode == W)
		data->key.w = 1;
	if (keycode == S)
		data->key.s = 1;
	if (keycode == A)
		data->key.a = 1;
	if (keycode == D)
		data->key.d = 1;
	if (keycode == RIGHT)
		data->game.right = 1;
	if (keycode == LEFT)
		data->game.left = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W)
		data->key.w = 0;
	if (keycode == S)
		data->key.s = 0;
	if (keycode == A)
		data->key.a = 0;
	if (keycode == D)
		data->key.d = 0;
	if (keycode == RIGHT)
		data->game.right = 0;
	if (keycode == LEFT)
		data->game.left = 0;
	return (0);
}
