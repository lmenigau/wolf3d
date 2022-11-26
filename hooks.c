/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 18:10:25 by lmenigau          #+#    #+#             */
/*   Updated: 2022/11/25 05:32:21 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "wolf3d.h"

void	key_press(int keycode, int *keys)
{
	printf("%d\n", keycode);
	if (keycode == 53)
		exit(0);
	if (keycode < 280)
		keys[keycode] = 1;
}

void	key_release(int keycode, int *keys)
{
	printf("%d\n", keycode);
	if (keycode < 280)
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
	mlx_hook(data->win, 2, 1L<<0, (int (*)())key_press, data->keys);
	mlx_hook(data->win, 3, 1L<<1, (int (*)())key_release, data->keys);
	mlx_hook(data->win, 17, 0, (int (*)())exit, NULL);
	mlx_loop_hook(data->mlx, (int (*)())loop, data);
}
