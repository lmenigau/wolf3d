/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 18:10:25 by lmenigau          #+#    #+#             */
/*   Updated: 2017/10/28 18:10:25 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "wolf3d.h"

void	key_press(int keycode, int *keys)
{
	if (keycode == 53)
		exit(0);
	keys[keycode] = 1;
}

void	key_release(int keycode, int *keys)
{
	keys[keycode] = 0;
}

void	loop(t_data *data)
{
	key_moves(data);
	raycast2(&data->world, &data->player);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	fps_counter(data);
}

void	place_hooks(t_data *data)
{
	mlx_hook(data->win, 2, 0, (int (*)())key_press, data->keys);
	mlx_hook(data->win, 3, 0, (int (*)())key_release, data->keys);
	mlx_hook(data->win, 17, 0, (int (*)())exit, NULL);
	mlx_loop_hook(data->mlx, (int (*)())loop, data);
}
